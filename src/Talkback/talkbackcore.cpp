#include "talkbackcore.h"
#include "TalkBackCommonTool.h"
#include "AudioData.h"
#include "vlog.h"
TalkbackCore::TalkbackCore():
    m_pRtsp(NULL),
    m_pRtspInfo(NULL),
    m_pTalkbackContext(NULL),
    m_pAudioDataContext(NULL),
    m_tThreadId(0),
    m_bThreadStop(true),
    m_bStartTalkback(false)
{

}

bool TalkbackCore::checkClientIsSupportTalkback()
{
    return checkClientIsSupportMicrophone();
}
static TALKBACK_THREAD_RET_TYPE startCaptureThreadEx(void *arg){
    TalkbackCore* pContext=(TalkbackCore*)arg;
    pContext->startCodeThread(arg);
}
bool TalkbackCore::initTalkback(lpTalkbackContext parm)
{
    m_bThreadStop=false;
    m_pTalkbackContext=parm;
#ifdef WIN32
    m_tThreadId=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)startCaptureThreadEx,(PVOID)this,0,NULL);
    ResumeThread(m_tThreadId);
#else
    pthread_create(&m_tThreadId,NULL,startCaptureThreadEx,this);
#endif
    INFO_PRINT("initCapture, start run audioDataCapture thread");
    return true;
}

bool TalkbackCore::deinitTalkback()
{
    m_bThreadStop=true;
    INFO_PRINT("deinitTalkback,wait for thread end");
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
    m_bStartTalkback=false;
    m_pTalkbackContext=NULL;
    INFO_PRINT("deinitTalkback thread end");
    return true;
}

bool TalkbackCore::startTalkback()
{
    if(m_bThreadStop==false){
        m_bStartTalkback=true;
        return true;
    }else{
        return false;
    }
}

bool TalkbackCore::pauseTalkback()
{
    m_bStartTalkback=false;
    return true;
}
typedef enum __tagTalkbackCoreThreadStep{
    TalkbackCoreThreadStep_init,
    TalkbackCoreThreadStep_setup_rtsp,
    TalkbackCoreThreadStep_init_audioData,
    TalkbackCoreThreadStep_play_rtsp,
    TalkbackCoreThreadStep_init_rtp,
    TalkbackCoreThreadStep_sendbuf_rtp,
    TalkbackCoreThreadStep_read_data,
    TalkbackCoreThreadStep_teardown_rtsp,
    TalkbackCoreThreadStep_keepalive_rtsp,
    TalkbackCoreThreadStep_default,
    TalkbackCoreThreadStep_deinit,
}tagTalkbackCoreThreadStep;
TALKBACK_THREAD_RET_TYPE TalkbackCore::startCodeThread(void *arg){
    bool bStop=false;
    tagTalkbackCoreThreadStep tStep=TalkbackCoreThreadStep_init;
    bool bIsRtspPlay=false;
    bool bListFlags_keepalive=true;
    bool bListFlags_sendAudioData=true;
    bool bListFlags_readData=true;
    while (bStop==false) {
        switch (tStep) {
        case TalkbackCoreThreadStep_init:{
                if(talkbackCoreThreadStep_init()){
                    tStep=TalkbackCoreThreadStep_setup_rtsp;
                    INFO_PRINT("TalkbackCoreThreadStep_init success");
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                    INFO_PRINT("TalkbackCoreThreadStep_init fail");
                }
            }
            break;
        case TalkbackCoreThreadStep_setup_rtsp:{
                if(talkbackCoreThreadStep_setup_rtsp()){
                    tStep=TalkbackCoreThreadStep_init_audioData;
                    m_pRtspInfo->session_lastTime=TalkbackThread::currentTime()/1000;
                    m_pRtspInfo->audioDataCheckTime=TalkbackThread::currentTime();
                    INFO_PRINT("TalkbackCoreThreadStep_setup_rtsp success");
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                    INFO_PRINT("TalkbackCoreThreadStep_setup_rtsp fail");
                }
            }
            break;
        case TalkbackCoreThreadStep_init_audioData:{
            if(talkbackCoreThreadStep_init_audioData()){
                tStep=TalkbackCoreThreadStep_play_rtsp;
            }else{
                tStep=TalkbackCoreThreadStep_deinit;
                INFO_PRINT("talkbackCoreThreadStep_init_audioData fail");
            }
        }
        case TalkbackCoreThreadStep_play_rtsp:{
                if(talkbackCoreThreadStep_play_rtsp()){
                    tStep=TalkbackCoreThreadStep_init_rtp;
                    bIsRtspPlay=true;
                    m_pRtspInfo->startPlayTime=TalkbackThread::currentTime();
                    INFO_PRINT("TalkbackCoreThreadStep_play_rtsp success");
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                    INFO_PRINT("TalkbackCoreThreadStep_play_rtsp fail");
                }
            }
            break;
        case TalkbackCoreThreadStep_init_rtp:{
                if(talkbackCoreThreadStep_init_rtp()){
                    tStep=TalkbackCoreThreadStep_default;
                    INFO_PRINT("TalkbackCoreThreadStep_init_rtp success");
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                    INFO_PRINT("TalkbackCoreThreadStep_init_rtp fail");
                }
            }
            break;
        case TalkbackCoreThreadStep_sendbuf_rtp:{
                if(talkbackCoreThreadStep_sendbuf_rtp()){
                    tStep=TalkbackCoreThreadStep_default;
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                }
            }
            break;
        case TalkbackCoreThreadStep_read_data:{
                if(talkbackCoreThreadStep_read_data()){
                    tStep=TalkbackCoreThreadStep_default;
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                }
        }
            break;
        case TalkbackCoreThreadStep_teardown_rtsp:{
                talkbackCoreThreadStep_teardown_rtsp();
                tStep=TalkbackCoreThreadStep_deinit;
            }
            break;
        case TalkbackCoreThreadStep_keepalive_rtsp:{
                if(talkbackCoreThreadStep_keepalive_rtsp()){
                    tStep=TalkbackCoreThreadStep_default;
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                }
            }
            break;
        case TalkbackCoreThreadStep_default:{
                if(m_bThreadStop==false){
                    //循环调度 控制
                    if(bListFlags_keepalive==true){
                        bListFlags_keepalive=false;
                        if(isTimeToSendRtspKeepAlive()){
                           tStep=TalkbackCoreThreadStep_keepalive_rtsp;
                           goto DEFAULT_CONTROL;
                        }
                    }
                    if(bListFlags_sendAudioData==true){
                        bListFlags_sendAudioData=false;
                        if(isTimeToSendAudioBuffer()){
                           tStep=TalkbackCoreThreadStep_sendbuf_rtp;
                           goto DEFAULT_CONTROL;
                        }
                    }
                    if(bListFlags_readData==true){
                        bListFlags_readData=false;
                        int nRet=isTimeToReadSocketData();
                        if(nRet==1){
                            tStep=TalkbackCoreThreadStep_read_data;
                            goto DEFAULT_CONTROL;
                        }else if(nRet==0){
                            //do nothing
                        }else{
                            tStep=TalkbackCoreThreadStep_deinit;
                            goto DEFAULT_CONTROL;
                        }
                    }

                DEFAULT_CONTROL:
                    //reset flags
                    if(bListFlags_readData==false&&bListFlags_sendAudioData==false&&bListFlags_keepalive==false){
                        bListFlags_readData=true;
                        bListFlags_sendAudioData=true;
                        bListFlags_keepalive=true;
                    }
                    if(tStep!=TalkbackCoreThreadStep_default){
                        //go to do work
                    }else{
                        TalkbackThread::mSleep(10);
                    }
                }else{
                    if(bIsRtspPlay==true){
                        tStep=TalkbackCoreThreadStep_teardown_rtsp;
                    }else{
                        tStep=TalkbackCoreThreadStep_deinit;
                    }
                }
            }
            break;
        case TalkbackCoreThreadStep_deinit:{
                talkbackCoreThreadStep_deinit_audioData();
                talkbackCoreThreadStep_deinit_rtp();
                talkbackCoreThreadStep_deinit();
                bStop=true;
            }
            break;
        }
    }
    INFO_PRINT("TalkbackCore thread end");
}

bool TalkbackCore::talkbackCoreThreadStep_init()
{
    if(NULL!=m_pRtsp){
        m_pRtsp->deinit();
        delete m_pRtsp;
        m_pRtsp=NULL;
    }

    m_pRtsp=new TalkbackRtsp;
    if(NULL!=m_pRtspInfo){
        deinitRtspInfo();
    }

    initRtspInfo();
    m_pRtsp->init(m_pRtspInfo);
    return true;
}

void TalkbackCore::talkbackCoreThreadStep_deinit()
{

}

bool TalkbackCore::talkbackCoreThreadStep_setup_rtsp()
{
    return m_pRtsp->setup();
}
void errorCallback(void *parm,tagTalkbackAudioError tError,char *pErrorInfo){
}
bool TalkbackCore::talkbackCoreThreadStep_init_audioData()
{
    if(m_pAudioDataContext==NULL){
        m_pAudioDataContext=new tagAudioContext;
        m_pAudioDataContext->pUserContext=this;
        m_pAudioDataContext->pAudioDataContext=NULL;
    }
    for(int n=0;n<m_pRtspInfo->sdp->media_num;n++){
        if(m_pRtspInfo->sdp->media[n].bRtspSetUp==1){
            Attribute_t attr;
            if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[n].media_n.type,
                                  SDP_ATTR_RTP_MAP,(void*)&attr,n)==RTSP_RET_FAIL){
                continue;
            }
            if(strcmp(attr.rtpmap.codec_type,"PCMA")==0){
                m_pRtspInfo->tAudioCodeMode=AUDIO_CODE_G711_A;
            }else if(strcmp(attr.rtpmap.codec_type,"PCMU")==0){
                m_pRtspInfo->tAudioCodeMode=AUDIO_CODE_C711_U;
            }else{
                INFO_PRINT("talkbackCoreThreadStep_init_audioData fail as do not support the audio type");
                return false;
            }
            m_pRtspInfo->rtpMap.freq=attr.rtpmap.freq;
            m_pRtspInfo->rtpMap.payload_type=attr.rtpmap.payload_type;
            memcpy(m_pRtspInfo->rtpMap.codec_type,attr.rtpmap.codec_type,strlen(attr.rtpmap.codec_type));
            bool bRet=applyAudio(m_pAudioDataContext,m_pRtspInfo->tAudioCodeMode,errorCallback);
            if(bRet==false){
                INFO_PRINT("talkbackCoreThreadStep_init_audioData fail as applyAudio fail");
            }
            return bRet;
        }else{
            continue;
        }
    }
    return true;
}

void TalkbackCore::talkbackCoreThreadStep_deinit_audioData()
{
    //fix me
}

bool TalkbackCore::talkbackCoreThreadStep_play_rtsp()
{
    return m_pRtsp->play();
}

bool TalkbackCore::talkbackCoreThreadStep_init_rtp()
{
    return true;
}

void TalkbackCore::talkbackCoreThreadStep_deinit_rtp()
{
//fix me
}
uint64_t g_nTime=0;
bool TalkbackCore::talkbackCoreThreadStep_sendbuf_rtp()
{
    int nSize=0;
    int nBuffsize=getSpecAudioCodeModeFrameBuffSize(m_pRtspInfo->tAudioCodeMode);
    char *pBuffer=new char[nBuffsize];
    memset(pBuffer,0,nBuffsize);
    bool bRet=true;
    long long nTimeStamp=0;
    while(bRet){
        if(m_pAudioDataContext->pAudioDataContext!=NULL){
            bRet=getData(m_pAudioDataContext,pBuffer,nBuffsize,nSize,nTimeStamp);
            if(bRet){
                int nDiv=nTimeStamp-g_nTime;
                g_nTime=nTimeStamp;
                //INFO_PRINT(nDiv);
                //等待修正
                if(nTimeStamp==0){
                    printf("nSize:%d;nDiv:%d;nTimeStamp:%lld\n",nSize,nDiv,nTimeStamp);
                }

                if(nDiv<0){
                    printf("error data:nDiv:%d;nTimeStamp:%lld\n",nDiv,nTimeStamp);
                    return true;
                }
                //send
                if(m_pRtspInfo->startPlayTime>nTimeStamp){
                    //do nothing
                    continue;
                }
                unsigned int nInterval=nTimeStamp-m_pRtspInfo->startPlayTime;//时间间隔
                //频率 m_pRtspInfo->rtpMap.freq
                int freq=m_pRtspInfo->rtpMap.freq;//采样频率
                m_pRtspInfo->rtptime;//rtp 开始时间
                uint32_t ts=m_pRtspInfo->rtptime+freq*nInterval/1000;
                if(NULL!=m_pRtspInfo->pRtp_audio){
                    if(m_pRtspInfo->pRtp_audio->sendbuf(pBuffer,nSize,ts)){
                        //keep going
                    }else{
                        INFO_PRINT("talkbackCoreThreadStep_sendbuf_rtp fail as sendbuf fail");
                        VLOG(VLOG_ERROR,"send buffer fail,bufferSize:%d",nSize);
                        return false;
                    }
                }else{
                    INFO_PRINT("talkbackCoreThreadStep_sendbuf_rtp fail as m_pRtspInfo->pRtp_audio is null");
                    return false;
                }
            }
        }else{
            bRet=false;
        }
    }
    return true;
}

bool TalkbackCore::talkbackCoreThreadStep_read_data()
{
    int nRet;
    if(m_pRtspInfo->b_interleavedMode==true){
        //fix me
        //暂时不实现这种模式
    }else{
        if(FD_ISSET(m_pRtspInfo->rtspSocket,&m_pRtspInfo->read_set)){
            //处理rtsp socket 信息
        }
        if(m_pRtspInfo->pRtcp_audio!=NULL){
            //处理rtcp audio 信息
        }
        if(m_pRtspInfo->pRtcp_video!=NULL){
            //处理 rtcp video 信息
            //暂时不做处理
        }
        if(m_pRtspInfo->pRtp_audio!=NULL){
            //处理 rtp audio 信息
        }
        if(m_pRtspInfo->pRtp_video!=NULL){
            //处理 rtp video 信息
            // 暂不做处理
        }
    }
}

void TalkbackCore::talkbackCoreThreadStep_teardown_rtsp()
{
    return m_pRtsp->teardown();
}

bool TalkbackCore::talkbackCoreThreadStep_keepalive_rtsp()
{
    return m_pRtsp->keepalive();
}

bool TalkbackCore::isTimeToSendRtspKeepAlive()
{
    uint64_t session_currentTime=TalkbackThread::currentTime()/1000;//单位秒
    //默认比timeout的时间 提早5s发送
    if((session_currentTime+5-m_pRtspInfo->session_lastTime)>10){
        m_pRtspInfo->session_lastTime=session_currentTime;
        return true;
    }else{
        return false;
    }
}

bool TalkbackCore::isTimeToSendAudioBuffer()
{
    if(m_bStartTalkback==true){
        uint64_t currentTime=TalkbackThread::currentTime();//单位毫秒
        if(currentTime-m_pRtspInfo->audioDataCheckTime>10){
            m_pRtspInfo->audioDataCheckTime=currentTime;
            return true;
        }
    }else{

    }
    return false;
}

int TalkbackCore::isTimeToReadSocketData()
{
    //暂时不实现 接受数据
    return 0;
    struct timeval timeout;
    FD_ZERO(m_pRtspInfo->read_set);
    int nMax_sock=0;
    if(m_pRtspInfo->pRtcp_audio!=NULL){

    }
    if(m_pRtspInfo->pRtcp_video!=NULL){
        //fix me
        //暂时不实现
    }
    if(m_pRtspInfo->pRtp_audio!=NULL){
        tagTalkbackRtpInfo *rtpAudioInfo=m_pRtspInfo->pRtp_audio->getRtpInfo();
        if(rtpAudioInfo->rtp_sock!=-1){
            FD_SET(rtpAudioInfo->rtp_sock,&m_pRtspInfo->read_set);
            if(rtpAudioInfo->rtp_sock>nMax_sock){
                nMax_sock=rtpAudioInfo->rtp_sock;
            }else{
                //do nothing
            }
        }else{
            //do nothing
        }
    }
    if(m_pRtspInfo->pRtp_video!=NULL){
        //fix me
        //暂时不实现
    }
    timeout.tv_sec=0;
    timeout.tv_usec=10*1000;//10 ms
    int nRet=select(nMax_sock+1,&m_pRtspInfo->read_set,NULL,NULL,&timeout);
    if(nRet<0){
        VLOG(VLOG_ERROR,"select failed");
        //应该停止服务
        return -1;
    }else if(nRet==0){
        int connect_status;
        SOCKLEN_t connect_len;
        connect_len=sizeof(connect_status);
        if(getsockopt(m_pRtspInfo->rtspSocket,SOL_SOCKET,SO_ERROR,(char *)&connect_status,&connect_len)<0){
            VLOG(VLOG_ERROR,"rtspc:socket disconnect ,errno:%d",errno);
            //应该停止服务
            return -1;
        }else{
            if(connect_status!=0){
                VLOG(VLOG_ERROR,"rtspc:socket disconnect ,errno:%d",errno);
                //应该停止服务
                return -1;
            }
            //time out
        }
        return 0;
    }else{
        return 1;
    }
    return 0;
}

void TalkbackCore::initRtspInfo()
{
    m_pRtspInfo=new tagTalkbackRtspInfo;
    m_pRtspInfo->role=RTSP_CLIENT;
    memset(m_pRtspInfo->userName,0,sizeof(m_pRtspInfo->userName));
    memcpy(m_pRtspInfo->userName,m_pTalkbackContext->userName,strlen(m_pTalkbackContext->userName));
    memset(m_pRtspInfo->passWord,0,sizeof(m_pRtspInfo->passWord));
    memcpy(m_pRtspInfo->passWord,m_pTalkbackContext->passWord,strlen(m_pTalkbackContext->passWord));
    m_pRtspInfo->nPort=m_pTalkbackContext->nPort;
    memset(m_pRtspInfo->url,0,sizeof(m_pRtspInfo->url));
    memcpy(m_pRtspInfo->url,m_pTalkbackContext->url,strlen(m_pTalkbackContext->url));
    memset(m_pRtspInfo->ip,0,sizeof(m_pRtspInfo->ip));
    memcpy(m_pRtspInfo->ip,m_pTalkbackContext->ip,strlen(m_pTalkbackContext->ip));
    memset(m_pRtspInfo->streamName,0,sizeof(m_pRtspInfo->streamName));
    sscanf(m_pRtspInfo->url,"rtsp://%*[^/]/%s",m_pRtspInfo->streamName);
    memset(m_pRtspInfo->session_id,0,sizeof(m_pRtspInfo->session_id));
    m_pRtspInfo->rtspSocket=-1;
    m_pRtspInfo->payloadSize=0;
    m_pRtspInfo->cseq=0;
    m_pRtspInfo->bLogin=true;
    m_pRtspInfo->sdp=NULL;
    m_pRtspInfo->session_timeout=60;
    m_pRtspInfo->auth=NULL;
    m_pRtspInfo->rtpseq=0;
    m_pRtspInfo->rtptime=0;
    m_pRtspInfo->stream_type = RTSP_STREAM_VIDEO | RTSP_STREAM_AUDIO;
    m_pRtspInfo->buffer_time=0;
    m_pRtspInfo->low_transport=RTP_TRANSPORT_UDP;
    m_pRtspInfo->cast_type=RTP_UNICAST;
    m_pRtspInfo->client_port=0;
    m_pRtspInfo->server_port=0;
    m_pRtspInfo->channel=0;
    m_pRtspInfo->ssrc=0;
    m_pRtspInfo->work_mode=RTSP_MODE_PLAY;
    m_pRtspInfo->transport=RTP_AUTO;
    m_pRtspInfo->pRtp_audio=NULL;
    m_pRtspInfo->pRtp_video=NULL;
    m_pRtspInfo->pRtcp_audio=NULL;
    m_pRtspInfo->pRtcp_video=NULL;
    m_pRtspInfo->pSocketGroup=new RTSP_SOCKET_GROUP;
    m_pRtspInfo->pSocketGroup->rtcp_port=0;
    m_pRtspInfo->pSocketGroup->rtcp_socket=-1;
    m_pRtspInfo->pSocketGroup->rtp_port=0;
    m_pRtspInfo->pSocketGroup->rtp_socket=-1;
}

void TalkbackCore::deinitRtspInfo()
{
    //fix me
    delete m_pRtspInfo;
    m_pRtspInfo=NULL;
}


