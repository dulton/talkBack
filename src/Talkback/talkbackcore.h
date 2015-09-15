#ifndef TALKBACKCORE_H
#define TALKBACKCORE_H
#include "TalkBackDataTypeCommon.h"
#include "talkbackthread.h"
#include "talkbackrtp.h"
#include "talkbackrtsp.h"
#include "talkbacklock.h"

typedef struct __tagTalkbackCoreEventCallbackState{
    bool state;
    bool bExistError;
    tagTalkbackCInterfaceError tError;
    char *pMessage;
}tagTalkbackCoreEventCallbackState;

class TalkbackCore
{
public:
    TalkbackCore();
    ~TalkbackCore();
    static bool checkClientIsSupportTalkback();
    bool initTalkback(lpTalkbackContext parm);
    bool deinitTalkback();
    bool startTalkback();
    bool pauseTalkback();


    TALKBACK_THREAD_RET_TYPE startCodeThread(void *arg);

    void talkbackCoreErrorCallbackEx(tagTalkbackAudioError tError,char *pErrorInfo);
private:
    bool talkbackCoreThreadStep_init();
    void talkbackCoreThreadStep_deinit();
    bool talkbackCoreThreadStep_setup_rtsp(int &nFlags);
    bool talkbackCoreThreadStep_init_audioData(int &nFlags);
    void talkbackCoreThreadStep_deinit_audioData();
    bool talkbackCoreThreadStep_play_rtsp();
    bool talkbackCoreThreadStep_init_rtp();
    void talkbackCoreThreadStep_deinit_rtp();
    bool talkbackCoreThreadStep_sendbuf_rtp();
    bool talkbackCoreThreadStep_read_data();
    void talkbackCoreThreadStep_teardown_rtsp();
    bool talkbackCoreThreadStep_keepalive_rtsp();
    void talkbackCoreThreadStep_audio_eventcallback();

    bool isTimeToSendRtspKeepAlive();
    bool isTimeToSendAudioBuffer();
    int isTimeToReadSocketData();//-1:错误,0:无数据可读,1:有数据可读
    bool isExistEventCallback();
    void initRtspInfo();
    void deinitRtspInfo();
    void eventCallback(tagTalkbackCInterfaceError tError,char *pError);
private:
    volatile bool m_bThreadStop;
    TALKBACK_THREAD_HANDLE m_tThreadId;
    volatile bool m_bStartTalkback;
    lpTalkbackContext m_pTalkbackContext;
    TalkbackRtsp *m_pRtsp;
    tagTalkbackRtspInfo *m_pRtspInfo;

    tagAudioContext *m_pAudioDataContext;
    tagTalkbackCoreEventCallbackState m_tEventCallbackState;
    TalkbackLock *m_pEventCallbackStateLock;
};

#endif // TALKBACKCORE_H
