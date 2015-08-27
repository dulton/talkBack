#include "talkbackaudiodatacapture.h"
#include "TalkBackCommonTool.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"


#define CAPTURE_BUFFER_LENGTH_MIN 320        //这个每次捕捉音源数据的数据长度
#define SAMPLING_RATE             8000      //这个采集音源数据样本的频率，这个变量很重要，关系到你是否能够采集到样本


TalkbackAudioDataCapture::TalkbackAudioDataCapture()
{
    for(int i=0;i<AUDIO_CODE_MODE_SIZE;i++){
        m_pContexList[i]=NULL;
    }
    m_bThreadStop=true;
    m_tThreadId=0;
    m_bClientIsSupportTalkback=false;
    m_pCaptureCallbackList=NULL;
}

TalkbackAudioDataCapture::~TalkbackAudioDataCapture()
{

}

bool TalkbackAudioDataCapture::checkClientIsSupportTalkback()
{
    if(m_bClientIsSupportTalkback){
        return m_bClientIsSupportTalkback;
    }else{
        return reCheckClientIsSupportTalkback();
    }
}
static TALKBACK_THREAD_RET_TYPE startCaptureThreadEx(void *arg){
    TalkbackAudioDataCapture *pContext=(TalkbackAudioDataCapture*)arg;
    pContext->startCodeThread(arg);
}
void TalkbackAudioDataCapture::initCapture()
{
    //创建线程
    m_bThreadStop=false;
#ifdef WIN32
    m_tThreadId=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)startCaptureThreadEx,(PVOID)this,0,NULL);
    ResumeThread(m_tThreadId);
#else
    pthread_create(&m_tThreadId,NULL,startCaptureThreadEx,this);
#endif
    INFO_PRINT("initCapture, start run audioDataCapture thread");
}

void TalkbackAudioDataCapture::deinitCapture()
{
    //销毁线程
    m_bThreadStop=true;
    INFO_PRINT("deinitCapture,wait for thread end");
#ifdef WIN32
    if(m_tThreadId){
        WaitForSingleObject(m_tThreadId,INFINITE);
        CloseHandle(m_tThreadId);
        m_tThreadId=0;
    }
#else
    if(m_tThreadId){
        pthread_join(m_tThreadId,NULL);
        m_tThreadId=0;
    }
#endif
    INFO_PRINT("deinitCapture thread end");
}

void TalkbackAudioDataCapture::addCodeToCapture(tagCapureContexInfo *pContexInfo)
{
    m_tContextListLock.lock();
    if(pContexInfo!=NULL){
        m_pContexList[pContexInfo->tCodeMode]=pContexInfo;
    }
    m_tContextListLock.unlock();
}

void TalkbackAudioDataCapture::removeCodeFromCapture(tagCapureContexInfo *pContexInfo)
{
    m_tContextListLock.lock();
    if(pContexInfo!=NULL){
        m_pContexList[pContexInfo->tCodeMode]=NULL;
    }
    m_tContextListLock.unlock();
}
void TalkbackAudioDataCapture::setCaptureErrorCallbackFunc(void *parm,AudioDataCaptureErrorCallback pFunc){
    // 测试此处是否 node 是否成功添加到 链表中
    m_tCaptureCallbackListLock.lock();
    if(m_pCaptureCallbackList==NULL){
        m_pCaptureCallbackList=new tagAudioCaptureCallbackStruct;
        m_pCaptureCallbackList->parm=parm;
        m_pCaptureCallbackList->pCallBack=pFunc;
        m_pCaptureCallbackList->pNext=NULL;
        m_tCaptureCallbackListLock.unlock();
        return ;
    }else{
        tagAudioCaptureCallbackStruct *pEnd=m_pCaptureCallbackList;
        while(pEnd->pNext!=NULL){
            pEnd=pEnd->pNext;
        }
        pEnd->pNext=new tagAudioCaptureCallbackStruct;
        pEnd->parm=parm;
        pEnd->pCallBack=pFunc;
        pEnd->pNext=NULL;
        m_tCaptureCallbackListLock.unlock();
        return;
    }
}
void TalkbackAudioDataCapture::removeCaptureErrorCallbackFunc(void *parm){
   //测试一下情况：
   //目标处于队列中间，处于队列尾部，处于队列头
   //原始队列为空
   //原始队列中没有目标
    m_tCaptureCallbackListLock.lock();
    if(m_pCaptureCallbackList!=NULL){
        tagAudioCaptureCallbackStruct *pTarget=m_pCaptureCallbackList;

        bool bIsFind=false;
        while(pTarget!=NULL){
            if(pTarget->parm==parm){
                bIsFind=true;
                break;
            }else{
                pTarget=pTarget->pNext;
            }
        }
        if(bIsFind==true){
            //移除目标
            tagAudioCaptureCallbackStruct *pPreTarget=m_pCaptureCallbackList;
            while(pPreTarget!=NULL){
                //头结点的情况
                if(pTarget==m_pCaptureCallbackList){
                    //
                    if(m_pCaptureCallbackList->pNext!=NULL){
                        m_pCaptureCallbackList=m_pCaptureCallbackList->pNext;
                    }else{
                        m_pCaptureCallbackList=NULL;
                    }
                    delete pTarget;
                    break;
                }else{
                    //keep going
                }
                //结点在其他位置的情况
                if(pPreTarget->pNext==pTarget){
                    pPreTarget->pNext=pTarget->pNext;
                    delete pTarget;
                    break;
                }else{
                    pPreTarget=pPreTarget->pNext;
                }
            }
        }else{
            //donothing
        }
    }else{
        //do nothing
        INFO_PRINT("removeCaptureErrorCallbackFunc fail as m_pCaptureCallbackList is null");
    }
    m_tCaptureCallbackListLock.unlock();
}

int TalkbackAudioDataCapture::getFrameSize()
{
    return 2*CAPTURE_BUFFER_LENGTH_MIN;
}
static bool isOpenalExistError(char *pString){
    ALenum tError =alGetError();
    if(tError==AL_NO_ERROR){
        return true;
    }else{
        INFO_PRINT(pString);
        return false;
    }
}
static bool isDeviceStillEnable(){
     const ALCchar* devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
     //完成此处代码
     char pStr1[3]={0,'\\','0'};
     int n=strcmp(devices,pStr1);
     if(n==0){
        return false;
     }else{
        return true;
     }
}
static int audioDataCaptureStep_captureData(ALCdevice *pAudioDevice,char *pBuff)
{
//0:捕获完成一帧数据，1：还没有捕获到一帧数据，2：捕获设备失败
    if(pAudioDevice!=NULL){
        ALint nSample=0;
        alcGetIntegerv(pAudioDevice,ALC_CAPTURE_SAMPLES,1,&nSample);
        if(nSample>=CAPTURE_BUFFER_LENGTH_MIN){
            memset(pBuff,0,(CAPTURE_BUFFER_LENGTH_MIN*2)*sizeof(char));
            alcCaptureSamples(pAudioDevice,pBuff,CAPTURE_BUFFER_LENGTH_MIN);
            return 0;
        }else{
            return 1;
        }
    }else{
        INFO_PRINT("audioDataCaptureStep_captureData fail as pAudioDevice is Null");
        return 2;
    }
}
typedef enum __tagAudioDataCaptureStep{
    AudioDataCaptureStep_init,
    AudioDataCaptureStep_enableCaptureDevice,
    AudioDataCaptureStep_captureData,
    AudioDataCaptureStep_dispatachData,
    AudioDataCaptureStep_default,
    AudioDataCaptureStep_deinit,
}tagAudioDataCaptureStep;
TALKBACK_THREAD_RET_TYPE TalkbackAudioDataCapture::startCodeThread(void *arg){
    bool bStop=false;
    bool bSleep=false;
    tagAudioDataCaptureStep tStep=AudioDataCaptureStep_init;
    ALCdevice *tAudioDevice=NULL;
    int nCount=50;
    char *pBuff=new char[2*CAPTURE_BUFFER_LENGTH_MIN];
    while(bStop==false){
        switch(tStep){
        case AudioDataCaptureStep_init:{
                //初始化
            INFO_PRINT("AudioDataCaptureStep_init,start capture audio data");
            tStep=AudioDataCaptureStep_enableCaptureDevice;

        }
            break;
        case AudioDataCaptureStep_enableCaptureDevice:{
                //初始化音频捕获设备
                if(tAudioDevice!=NULL){
                    alcCaptureStop(tAudioDevice);
                    alcCaptureCloseDevice(tAudioDevice);
                    tAudioDevice=NULL;
                }
                tAudioDevice=alcCaptureOpenDevice(NULL,SAMPLING_RATE,AL_FORMAT_MONO16,CAPTURE_BUFFER_LENGTH_MIN);
                if(tAudioDevice==NULL){
                    m_bClientIsSupportTalkback=false;
                    tStep=AudioDataCaptureStep_default;
                    break;
                }else{
                }
                alcCaptureStart(tAudioDevice);
                if(isOpenalExistError("alcCaptureStart error")==false){
                    m_bClientIsSupportTalkback=false;
                    tStep=AudioDataCaptureStep_default;
                    break;
                }else{
                }
                m_bClientIsSupportTalkback=true;
                tStep=AudioDataCaptureStep_default;

        }
            break;
        case AudioDataCaptureStep_captureData:{
                //捕获音频数据
            int nRet=audioDataCaptureStep_captureData(tAudioDevice,pBuff);
            //0:捕获完成一帧数据，1：还没有捕获到一帧数据，2：捕获设备失败
            if(nRet==0){
                //下一步分发
                tStep=AudioDataCaptureStep_dispatachData;
            }else if(nRet==1){
                //睡眠，回到default
                tStep=AudioDataCaptureStep_default;
                bSleep=true;
            }else{
                // 设备出错，跳转到初始化音频捕获设备
                m_bClientIsSupportTalkback=false;
                tStep=AudioDataCaptureStep_default;
                INFO_PRINT("AudioDataCaptureStep_captureData fail as device error");
            }
            //大约 1S中检测一次 录音设备是否还在工作
            nCount++;
            if(nCount>50){
                nCount=0;
                if(!isDeviceStillEnable){
                    m_bClientIsSupportTalkback=false;
                    tStep=AudioDataCaptureStep_default;
                    //调用回调，告知外界
                    errorCallBack(DataCapture_Microphone_Undetect,"Microphone device can not been detect");
                }
            }
        }
            break;
        case AudioDataCaptureStep_dispatachData:{
                //分发音频数据
            audioDataCaptureStep_dispatachData(pBuff);
            tStep=AudioDataCaptureStep_default;
        }
            break;
        case AudioDataCaptureStep_default:{
                //休眠，或检测其他状态
            if(m_bThreadStop==false){
                if(m_bClientIsSupportTalkback==true){
                    //
                    if(bSleep){
                        TalkbackThread::mSleep(10);
                    }else{
                        //do nothing
                    }
                    tStep=AudioDataCaptureStep_captureData;
                }else{
                    //硬件不支持
                    tStep=AudioDataCaptureStep_enableCaptureDevice;
                    TalkbackThread::mSleep(100);
                }
            }else{
                tStep=AudioDataCaptureStep_deinit;
            }
        }
            break;
        case AudioDataCaptureStep_deinit:{
                //回收资源
            if(NULL!=tAudioDevice){
                alcCaptureStop(tAudioDevice);
                alcCaptureCloseDevice(tAudioDevice);
            }
            //移除code 队列
            //调用回调，告知外界
            errorCallBack(DataCapture_Thread_Unwork,"deinit func been called");
            //移除回调队列
            bStop=true;
            INFO_PRINT("AudioDataCaptureStep_deinit,end capture audio data");
        }
            break;
        }
    }
}

bool TalkbackAudioDataCapture::reCheckClientIsSupportTalkback()
{
    TalkbackThread::mSleep(50);
    if(m_bThreadStop==false){
        return m_bClientIsSupportTalkback;
    }else{
        //check
        ALCdevice *device = alcCaptureOpenDevice(NULL, SAMPLING_RATE,AL_FORMAT_MONO16, CAPTURE_BUFFER_LENGTH_MIN);

        if(device){
            alcCaptureCloseDevice(device);
            return true;
        }else{
            alcCaptureCloseDevice(device);
            return false;
        }
    }

}



void TalkbackAudioDataCapture::errorCallBack(tagAudioDataCaptureError tError, char *pErrorInfo)
{
    m_tCaptureCallbackListLock.lock();
    if(NULL!=m_pCaptureCallbackList){
        tagAudioCaptureCallbackStruct *pTemp=m_pCaptureCallbackList;
        while(pTemp!=NULL){
            pTemp->pCallBack(pTemp->parm,tError,pErrorInfo);
            pTemp=pTemp->pNext;
        }
    }else{
        //do nothing
    }
    m_tCaptureCallbackListLock.unlock();
}
void TalkbackAudioDataCapture:: copyBuffToContexList(int n,int nMax,char *pBuff){
    //
    int nMin=nMax;
    int nPlace=0;//找到的目标位置
    for(int i=0;i<AUDIODATALISTSIZE;i++){
        if(m_pContexList[n]->tDataList[i].nTimeStamp==0){
            nPlace=i;//
            break;
        }
        if(nMin>m_pContexList[n]->tDataList[i].nTimeStamp){
            nMin=m_pContexList[n]->tDataList[i].nTimeStamp;
            nPlace=i;
        }else{
            //keep going
        }
    }
    m_pContexList[n]->tDataList[nPlace].nTimeStamp=nMax;
    m_pContexList[n]->tDataList[nPlace].nDataSize=CAPTURE_BUFFER_LENGTH_MIN*2;
    memcpy(m_pContexList[n]->tDataList[nPlace].pCaptureData,pBuff,CAPTURE_BUFFER_LENGTH_MIN*2);
}

void TalkbackAudioDataCapture::audioDataCaptureStep_dispatachData(char *pBuff)
{
    if(pBuff!=NULL){
        m_tContextListLock.lock();
        talkback_int64 tCurrentTime=TalkbackThread::currentTime();
        for(int i=0;i<AUDIO_CODE_MODE_SIZE;i++){
            if(m_pContexList[i]!=NULL){
                m_pContexList[i]->pDataLock->lock();
                m_pContexList[i]->nCurrentTimeStamp=tCurrentTime;
                copyBuffToContexList(i,tCurrentTime,pBuff);
                m_pContexList[i]->pDataLock->unlock();
            }else{
                //do nothing
            }
        }
        m_tContextListLock.unlock();
    }else{
        //do nothing
    }
}
