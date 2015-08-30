#include "talkbackcore.h"
#include "TalkBackCommonTool.h"
TalkbackCore::TalkbackCore()
{
    m_tThreadId=0;
    m_bThreadStop=true;
    m_bStartTalkback=false;
    m_pTalkbackContext=NULL;
    m_pRtp=NULL;
    m_pRtsp=NULL;
}

bool TalkbackCore::checkClientIsSupportTalkback()
{

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
    TalkbackCoreThreadStep_play_rtsp,
    TalkbackCoreThreadStep_init_rtp,
    TalkbackCoreThreadStep_sendbuf_rtp,
    TalkbackCoreThreadStep_teardown_rtsp,
    TalkbackCoreThreadStep_keepalive_rtsp,
    TalkbackCoreThreadStep_default,
    TalkbackCoreThreadStep_deinit,
}tagTalkbackCoreThreadStep;
TALKBACK_THREAD_RET_TYPE TalkbackCore::startCodeThread(void *arg){
    bool bStop=false;
    tagTalkbackCoreThreadStep tStep=TalkbackCoreThreadStep_init;
    bool bIsRtspPlay=false;
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
                    tStep=TalkbackCoreThreadStep_play_rtsp;
                    INFO_PRINT("TalkbackCoreThreadStep_setup_rtsp success");
                }else{
                    tStep=TalkbackCoreThreadStep_deinit;
                    INFO_PRINT("TalkbackCoreThreadStep_setup_rtsp fail");
                }
            }
            break;
        case TalkbackCoreThreadStep_play_rtsp:{
                if(talkbackCoreThreadStep_play_rtsp()){
                    tStep=TalkbackCoreThreadStep_init_rtp;
                    bIsRtspPlay=true;
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
                    if(isTimeToSendRtspKeepAlive()){
                        tStep=TalkbackCoreThreadStep_keepalive_rtsp;
                    }else{
                        if(isTimeToSendAudioBuffer()){
                        tStep=TalkbackCoreThreadStep_sendbuf_rtp;
                        }else{
                            //休眠
                        TalkbackThread::mSleep(10);
                        tStep=TalkbackCoreThreadStep_default;
                        }
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

            }
            break;
        }
    }
}

bool TalkbackCore::talkbackCoreThreadStep_init()
{
    if(NULL!=m_pRtsp){
        m_pRtsp->deinit();
        delete m_pRtsp;
        m_pRtsp=NULL;
    }
    if(NULL!=m_pRtp){
        m_pRtp->deinit();;
        delete m_pRtp;
        m_pRtp=NULL;
    }
    m_pRtp=new TalkbackRtp;
    m_pRtsp=new TalkbackRtsp;

}

bool TalkbackCore::talkbackCoreThreadStep_setup_rtsp()
{
    return m_pRtsp->setup();
}

bool TalkbackCore::talkbackCoreThreadStep_play_rtsp()
{
    return m_pRtsp->play();
}

bool TalkbackCore::talkbackCoreThreadStep_init_rtp()
{
    return m_pRtp->init(m_pRtpInfo);
}

bool TalkbackCore::talkbackCoreThreadStep_sendbuf_rtp()
{
    return m_pRtp->sendbuf();
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

}

bool TalkbackCore::isTimeToSendAudioBuffer()
{
    if(m_bStartTalkback){

    }else{

    }
    return false;
}

void TalkbackCore::initRtspInfo()
{

}

void TalkbackCore::deinitRtspInfo()
{

}

void TalkbackCore::initRtpInfo()
{

}

void TalkbackCore::deinitRtpInfo()
{

}
