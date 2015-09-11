#include "audiocode.h"
bool AudioCode::m_bIsSupportG711_Alaw=SupportG711_Alaw;
bool AudioCode::m_bIsSupportG711_Ulaw=SupportG711_Ulaw;
int AudioCode::m_nG711_Alaw_Size=G711_Alaw_Size;
int AudioCode::m_nG711_Ulaw_Size=G711_Ulaw_Size;

#include "talkbackaudiodatacapture.h"
#include "talkbacklock.h"
#include "TalkBackCommonTool.h"

#include "g711_2.h"
static TalkbackLock g_csAudioDataCapture;
static int g_nAudioDataCaptureCount=0;
static TalkbackAudioDataCapture *g_pCapture=NULL;

void applyCapture(){
    g_csAudioDataCapture.lock();
    if(g_nAudioDataCaptureCount==0){
        g_pCapture=new TalkbackAudioDataCapture;
        g_pCapture->initCapture();
        g_nAudioDataCaptureCount++;
    }else{
        g_nAudioDataCaptureCount++;
    }
    g_csAudioDataCapture.unlock();
}
void releaseCapture(){
    g_csAudioDataCapture.lock();
    if(g_nAudioDataCaptureCount>0){
        g_nAudioDataCaptureCount=g_nAudioDataCaptureCount-1;
        if(g_nAudioDataCaptureCount==0){
            g_pCapture->deinitCapture();
            delete g_pCapture;
            g_pCapture=NULL;
        }else{
            //do nothing
        }
    }else{
            //do nothing
    }
    g_csAudioDataCapture.unlock();
}
AudioCode::AudioCode()
{
    m_bCodeThreadStop=true;
    m_tCodeThreadId=0;
    applyCapture();
    m_pApplyAudioNodeList=NULL;
    m_pApplyAudioNodeListLock=new TalkbackLock;
    m_bNeedEncodeG711_Alaw=false;
    m_bNeedEncodeG711_Ulaw=false;
    m_nNeedEncodeCountG711_Alaw=0;
    m_nNeedEncodeCountG711_Ulaw=0;
}

AudioCode::~AudioCode()
{
    releaseCapture();
}

bool AudioCode::checkClientIsSupportTalkback()
{
    //return TalkbackAudioDataCapture::checkClientIsSupportTalkbackEx();
    applyCapture();
    int nRet=g_pCapture->checkClientIsSupportTalkback();
    releaseCapture();
    return nRet;
}

bool AudioCode::checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode)
{
    if(tCodeMode==AUDIO_CODE_G711_A){
        return m_bIsSupportG711_Alaw;
    }else if(tCodeMode==AUDIO_CODE_C711_U){
        return m_bIsSupportG711_Ulaw;
    }else{
        return false;
    }
}

int AudioCode::getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode)
{
    if(tCodeMode==AUDIO_CODE_G711_A){
        return m_nG711_Alaw_Size;
    }else if(tCodeMode==AUDIO_CODE_C711_U){
        return m_nG711_Ulaw_Size;
    }else{
        return 0;
    }
}

bool AudioCode::getData(void *parm, char *pBuff, int pBufferSize, int &nSize,talkback_int64 &nTimeStamp)
{
    nSize=0;
    nTimeStamp=0;
    m_pApplyAudioNodeListLock->lock();
    AudioCodeSpace::tagApplyAudioNode *pTemp=m_pApplyAudioNodeList;
    while(pTemp!=NULL){
        if(pTemp->parm==parm){
            int nMin=pTemp->nMaxTimeStamp;
            int nMax=pTemp->nMaxTimeStamp;
            int nPlace=0;
            for(int i=0;i<AUDIODATALISTSIZE;i++){
                pTemp->tDataNodeList[i].tTimeStamp;
                if(pTemp->tDataNodeList[i].tTimeStamp>0&&pTemp->tDataNodeList[i].tTimeStamp<=nMin){
                    nMin=pTemp->tDataNodeList[i].tTimeStamp;
                    nPlace=i;
                }else{
                    //
                }
            }
            if(pTemp->tDataNodeList[nPlace].nSize!=0&&pTemp->tDataNodeList[nPlace].nSize<=pBufferSize){
                memcpy(pBuff,pTemp->tDataNodeList[nPlace].pData,pTemp->tDataNodeList[nPlace].nSize);
                nTimeStamp=pTemp->tDataNodeList[nPlace].tTimeStamp;
                pTemp->tDataNodeList[nPlace].tTimeStamp=0;
                nSize=pTemp->tDataNodeList[nPlace].nSize;
                if(nSize==0&&nTimeStamp!=0){
                    INFO_PRINT("stop");
                }
                pTemp->tDataNodeList[nPlace].nSize=0;
            }
            break;
        }else{
            pTemp=pTemp->pNext;
        }
    }
    m_pApplyAudioNodeListLock->unlock();
    if(nSize==0){
        return false;
    }else{
        return true;
    }
}

bool AudioCode::applyAudio(void *parm, tagAudioCodeMode tCodeMode, AudioErrorCallback pErrorCallback)
{
    //
    int nSize=getSpecAudioCodeModeFrameBuffSize(tCodeMode);
    if(nSize==0){
        INFO_PRINT("applyAudio fail as tCodeMode do not supply");
        return false;
    }
    if(!releaseAudio(parm)){
        INFO_PRINT("applyAudio fail as releaseAudio old parm fail");
        return false;
    }
    m_pApplyAudioNodeListLock->lock();
    AudioCodeSpace::tagApplyAudioNode *pTemp;
    pTemp=new AudioCodeSpace::tagApplyAudioNode;
    pTemp->parm=parm;
    pTemp->pErrorCallback=pErrorCallback;
    pTemp->tCodeMode=tCodeMode;
    pTemp->pLock=new TalkbackLock;
    pTemp->pNext=NULL;
    pTemp->nMaxTimeStamp=0;
    for(int n=0;n<AUDIODATALISTSIZE;n++){
        pTemp->tDataNodeList[n].nSize=0;
        pTemp->tDataNodeList[n].pData=new char[nSize];
        pTemp->tDataNodeList[n].tTimeStamp=0;
    }
    if(m_pApplyAudioNodeList==NULL){
        m_pApplyAudioNodeList=pTemp;
    }else{
        AudioCodeSpace::tagApplyAudioNode *pNext=m_pApplyAudioNodeList;
        while(pNext->pNext!=NULL){
            pNext=pNext->pNext;
        }
        pNext->pNext=pTemp;
    }
    if(tCodeMode==AUDIO_CODE_G711_A){
        m_nNeedEncodeCountG711_Alaw++;
        m_bNeedEncodeG711_Alaw=true;
    }else if(tCodeMode==AUDIO_CODE_C711_U){
        m_nNeedEncodeCountG711_Ulaw++;
        m_bNeedEncodeG711_Ulaw=true;
    }else{

    }

    m_pApplyAudioNodeListLock->unlock();
    return true;
}

bool AudioCode::releaseAudio(void *parm)
{
    m_pApplyAudioNodeListLock->lock();
    AudioCodeSpace::tagApplyAudioNode *pHead=m_pApplyAudioNodeList;
    AudioCodeSpace::tagApplyAudioNode *pTemp=m_pApplyAudioNodeList;
    while(pTemp!=NULL){
        if(pTemp->parm==parm){
            //查找到目标
            if(pTemp->tCodeMode==AUDIO_CODE_G711_A){
                m_nNeedEncodeCountG711_Alaw--;
                if(m_nNeedEncodeCountG711_Alaw==0){
                    m_bNeedEncodeG711_Alaw=false;
                }
            }else if(pTemp->tCodeMode==AUDIO_CODE_C711_U){
                m_nNeedEncodeCountG711_Ulaw--;
                if(m_nNeedEncodeCountG711_Ulaw==0){
                    m_bNeedEncodeG711_Ulaw=false;
                }
            }
            delete pTemp->pLock;
            for(int n=0;n<AUDIODATALISTSIZE;n++){
                delete pTemp->tDataNodeList[n].pData;
            }
            if(pHead==m_pApplyAudioNodeList){
                m_pApplyAudioNodeList=m_pApplyAudioNodeList->pNext;
                delete pHead;
            }else{
                pHead->pNext=pTemp->pNext;
                delete pTemp;
            }
            break;
        }else{
            pHead=pTemp;
            pTemp=pTemp->pNext;
        }
    }
    m_pApplyAudioNodeListLock->unlock();
    return true;
}
static TALKBACK_THREAD_RET_TYPE startCodeThreadEx(void *arg){
    AudioCode *pContext=(AudioCode*)arg;
    pContext->startCodeThread(arg);
}
void AudioCode::initAudio()
{
    //创建编码线程
#ifdef WIN32
   // m_tCodeThreadId=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)startCodeThread,(PVOID)this,0,NULL);
    m_tCodeThreadId = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startCodeThreadEx, (PVOID)this, 0, NULL);
    // m_tCodeThreadId = CreateThread(NULL, 0, startCodeThread, (PVOID)this, 0, NULL);
#else
    pthread_create(&m_tCodeThreadId,NULL,startCodeThreadEx,this);
#endif
}

void AudioCode::deinitAudio()
{
    //销毁编码线程
    m_bCodeThreadStop=true;
#ifdef WIN32
    if(m_tCodeThreadId){
        WaitForSingleObject(m_tCodeThreadId,INFINITE);
        CloseHandle(m_tCodeThreadId);
        m_tCodeThreadId=0;
    }
#else
    if(m_tCodeThreadId){
        pthread_join(m_tCodeThreadId,NULL);
        m_tCodeThreadId=0;
    }
#endif
}
typedef enum __tagAudioCodeStep{
    tagAudioCodeStep_init,
    tagAudioCodeStep_enCodeData,
    tagAudioCodeStep_dispatachData,
    tagAudioCodeStep_default,
    tagAudioCodeStep_deinit,
}tagAudioCodeStep;
static void audioDataCaptureError(void *parm,tagAudioDataCaptureError tError,char *pErrorInfo){
    AudioCode* pTemp=(AudioCode*)parm;
    tagTalkbackAudioError tAudioError;
    if(tError==DataCapture_Thread_Unwork){
        tAudioError=AUDIO_MICROPHONE_UNDETECT;
    }else if(tError==DataCapture_Microphone_Undetect){
        tAudioError=AUDIO_MICROPHONE_UNDETECT;
    }else if(tError==DataCapture_Unknow_Error){
        tAudioError=AUDIO_UNKNOW_ERROR;
    }else {
        tAudioError=AUDIO_UNKNOW_ERROR;
    }
    pTemp->errorCallBack(tAudioError,pErrorInfo);
}
static bool checkIsReadyForEncode(tagCapureContexInfo *pG711_Alaw,tagCapureContexInfo *pG711_Ulaw,talkback_int64 nAlawCurrentTime,talkback_int64 nUlawCurrentTime,bool &bAlaw,bool &bUlaw)
{
    if(pG711_Alaw->nCurrentTimeStamp>nAlawCurrentTime){
        bAlaw=true;
    }
    if(pG711_Ulaw->nCurrentTimeStamp>nUlawCurrentTime){
        bUlaw=true;
    }
    if(bAlaw==true||bAlaw==true){
        return true;
    }else{
        return false;
    }
}
static bool AlawEncode(tagCapureContexInfo *pG711_Alaw,talkback_int64 &nCurrentTime, char *pBuff ){
    pG711_Alaw->pDataLock->lock();
    pG711_Alaw->tDataList;
    talkback_int64 nMix=pG711_Alaw->nCurrentTimeStamp;
    int nPlace=0;
    for(int n=0;n<AUDIODATALISTSIZE;n++){
        if(pG711_Alaw->tDataList[n].nTimeStamp>nCurrentTime&&pG711_Alaw->tDataList[n].nTimeStamp<nMix){
            nMix=pG711_Alaw->tDataList[n].nTimeStamp;
            nPlace=n;
        }
    }
    int nSize=pG711_Alaw->tDataList[nPlace].nDataSize;
    short pcm_val;
    char *buffer =pG711_Alaw->tDataList[nPlace].pCaptureData;

    nCurrentTime=pG711_Alaw->tDataList[nPlace].nTimeStamp;
    pG711_Alaw->tDataList[nPlace].nTimeStamp=0;
    pG711_Alaw->tDataList[nPlace].nDataSize=0;

    for(int i=0;i<nSize;i+=2){
        short LE= pcm_val=*((short *)(buffer+i));
        unsigned char alaw=linear2alaw(LE);
        memcpy(pBuff+i/2,&alaw,1);
    }
    pG711_Alaw->pDataLock->unlock();
    return true;
}

static bool UlawEncode(tagCapureContexInfo *pG711_Ulaw,talkback_int64 &nCurrentTime,char *pBuff){
    pG711_Ulaw->pDataLock->lock();
    pG711_Ulaw->tDataList;
    talkback_int64 nMix=pG711_Ulaw->nCurrentTimeStamp;
    int nPlace=0;
    for(int n=0;n<AUDIODATALISTSIZE;n++){
        if(pG711_Ulaw->tDataList[n].nTimeStamp>nCurrentTime&&pG711_Ulaw->tDataList[n].nTimeStamp<nMix){
            nMix=pG711_Ulaw->tDataList[n].nTimeStamp;
            nPlace=n;
        }
    }
    int nSize=pG711_Ulaw->tDataList[nPlace].nDataSize;
    short pcm_val;
    char *buffer =pG711_Ulaw->tDataList[nPlace].pCaptureData;
    nCurrentTime=pG711_Ulaw->tDataList[nPlace].nTimeStamp;
    pG711_Ulaw->tDataList[nPlace].nTimeStamp=0;
    pG711_Ulaw->tDataList[nPlace].nDataSize=0;
    for(int i=0;i<nSize;i+=2){
        short LE= pcm_val=*((short *)(buffer+i));
        unsigned char alaw=linear2alaw(LE);
        memcpy(pBuff+i/2,&alaw,1);
    }
    pG711_Ulaw->pDataLock->unlock();
    return true;
}
TALKBACK_THREAD_RET_TYPE AudioCode::startCodeThread(void *arg){
    m_bCodeThreadStop=false;
    bool bStop=false;
    tagAudioCodeStep tStep=tagAudioCodeStep_init;
    tagCapureContexInfo *pG711_Alaw;
    tagCapureContexInfo *pG711_Ulaw;
    bool bAlawReady=false;
    bool bUlawReady=false;
    bool bAlawEncodeReady=false;
    bool bUlawEncodeReady=false;
    char *pAlawEncodeBuff=new char[m_nG711_Alaw_Size];
    char *pUlawEnchodeBuff=new char[m_nG711_Ulaw_Size];
    talkback_int64 nAlawCurrentTime=0;
    talkback_int64 nUlawCurrentTime=0;
    while(bStop==false){
        switch(tStep){
            case tagAudioCodeStep_init:{
            //初始化
            pG711_Alaw=new tagCapureContexInfo;
            pG711_Ulaw=new tagCapureContexInfo;

            pG711_Alaw->pDataLock=new TalkbackLock;
            pG711_Alaw->tCodeMode=AUDIO_CODE_G711_A;
            pG711_Alaw->nCurrentTimeStamp=0;

            pG711_Ulaw->pDataLock=new TalkbackLock;
            pG711_Ulaw->tCodeMode=AUDIO_CODE_C711_U;
            pG711_Ulaw->nCurrentTimeStamp=0;

            int nBuffSize=TalkbackAudioDataCapture::getFrameSize();
            for(int i=0;i<AUDIODATALISTSIZE;i++){
                pG711_Alaw->tDataList[i].nDataSize=0;
                pG711_Alaw->tDataList[i].nTimeStamp=0;
                pG711_Alaw->tDataList[i].pCaptureData=new char[nBuffSize];

                pG711_Ulaw->tDataList[i].nDataSize=0;
                pG711_Ulaw->tDataList[i].nTimeStamp=0;
                pG711_Ulaw->tDataList[i].pCaptureData=new char[nBuffSize];
            }
            g_pCapture->addCodeToCapture(pG711_Alaw);
            g_pCapture->addCodeToCapture(pG711_Ulaw);
            g_pCapture->setCaptureErrorCallbackFunc((void *)this,audioDataCaptureError);
            tStep=tagAudioCodeStep_default;
        }
            break;
        case tagAudioCodeStep_enCodeData:{
            //编码数据
            if(bAlawReady&&m_bNeedEncodeG711_Alaw){
                bAlawReady=false;
                if(AlawEncode(pG711_Alaw,nAlawCurrentTime,pAlawEncodeBuff)){
                    bAlawEncodeReady=true;
                }
            }else{
            }
            if(bUlawReady&&m_bNeedEncodeG711_Ulaw){
                bUlawReady=false;
                if(UlawEncode(pG711_Ulaw,nUlawCurrentTime,pUlawEnchodeBuff)){
                    bUlawEncodeReady=true;
                }
            }else{
            }
            tStep=tagAudioCodeStep_dispatachData;
        }
            break;
        case tagAudioCodeStep_dispatachData:{
            //分发数据
            if(bAlawEncodeReady){
                disPatchBuff(pAlawEncodeBuff,AUDIO_CODE_G711_A,nAlawCurrentTime);
                bAlawEncodeReady=false;
            }
            if(bUlawEncodeReady){
                disPatchBuff(pUlawEnchodeBuff,AUDIO_CODE_C711_U,nUlawCurrentTime);
                bUlawEncodeReady=false;
            }
            tStep=tagAudioCodeStep_default;
        }
            break;
        case tagAudioCodeStep_default:{
            //
            if(m_bCodeThreadStop==false){
                if(checkIsReadyForEncode(pG711_Alaw,pG711_Ulaw,nAlawCurrentTime,nUlawCurrentTime,bAlawReady,bUlawReady)){
                    tStep=tagAudioCodeStep_enCodeData;
                }else{
                    TalkbackThread::mSleep(10);
                }
            }else{
                tStep=tagAudioCodeStep_deinit;
            }
        }
            break;
        case tagAudioCodeStep_deinit:{
            //退出
            bStop=true;
            g_pCapture->removeCodeFromCapture(pG711_Alaw);
            g_pCapture->removeCodeFromCapture(pG711_Ulaw);
            for(int i=0;i<AUDIODATALISTSIZE;i++){
                delete pG711_Alaw->tDataList[i].pCaptureData;
                delete pG711_Ulaw->tDataList[i].pCaptureData;
            }
            g_pCapture->removeCaptureErrorCallbackFunc((void*)this);
        }
            break;
        }
    }
}

void AudioCode::errorCallBack(tagTalkbackAudioError tError, char *pErrorInfo)
{
    m_pApplyAudioNodeListLock->lock();
    AudioCodeSpace::tagApplyAudioNode *pTemp=m_pApplyAudioNodeList;
    while(pTemp!=NULL){
        pTemp->pErrorCallback(pTemp->parm,tError,pErrorInfo);//考虑开一个线程，防止被外界阻塞内部线程
        pTemp=pTemp->pNext;
    }
    m_pApplyAudioNodeListLock->unlock();
}
void AudioCode::disPatchBuff(char *pBuff, tagAudioCodeMode tCodeMode,talkback_int64 nTimeStamp)
{
    m_pApplyAudioNodeListLock->lock();
    AudioCodeSpace::tagApplyAudioNode *pTemp=m_pApplyAudioNodeList;
    while(pTemp!=NULL){
        if(pTemp->tCodeMode==tCodeMode){
            pTemp->nMaxTimeStamp=nTimeStamp;
            pTemp->pLock->lock();
            talkback_int64 nMix=nTimeStamp;
            int nPlace=0;
            for(int i=0;i<AUDIODATALISTSIZE;i++){
                if(pTemp->tDataNodeList[i].tTimeStamp==0){
                    nPlace=i;
                    break;
                }
                if(pTemp->tDataNodeList[i].tTimeStamp<nMix){
                    nMix=pTemp->tDataNodeList[i].tTimeStamp;
                    nPlace=i;
                }else{

                }
            }
            pTemp->tDataNodeList[nPlace].tTimeStamp=nTimeStamp;
            pTemp->tDataNodeList[nPlace].nSize=AudioCode::getSpecAudioCodeModeFrameBuffSize(tCodeMode);
            memcpy(pTemp->tDataNodeList[nPlace].pData,pBuff,pTemp->tDataNodeList[nPlace].nSize);
            pTemp->pLock->unlock();
        }else{
        }
        pTemp=pTemp->pNext;
    }
    m_pApplyAudioNodeListLock->unlock();
}



