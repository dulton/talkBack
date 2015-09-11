#ifndef TALKBACKCORE_H
#define TALKBACKCORE_H
#include "TalkBackDataTypeCommon.h"
#include "talkbackthread.h"
#include "talkbackrtp.h"
#include "talkbackrtsp.h"
class TalkbackCore
{
public:
    TalkbackCore();
    static bool checkClientIsSupportTalkback();
    bool initTalkback(lpTalkbackContext parm);
    bool deinitTalkback();
    bool startTalkback();
    bool pauseTalkback();
    TALKBACK_THREAD_RET_TYPE startCodeThread(void *arg);
private:
    bool talkbackCoreThreadStep_init();
    void talkbackCoreThreadStep_deinit();
    bool talkbackCoreThreadStep_setup_rtsp();
    bool talkbackCoreThreadStep_init_audioData();
    void talkbackCoreThreadStep_deinit_audioData();
    bool talkbackCoreThreadStep_play_rtsp();
    bool talkbackCoreThreadStep_init_rtp();
    void talkbackCoreThreadStep_deinit_rtp();
    bool talkbackCoreThreadStep_sendbuf_rtp();
    bool talkbackCoreThreadStep_read_data();
    void talkbackCoreThreadStep_teardown_rtsp();
    bool talkbackCoreThreadStep_keepalive_rtsp();

    bool isTimeToSendRtspKeepAlive();
    bool isTimeToSendAudioBuffer();
    bool isTimeToReadSocketData();

    void initRtspInfo();
    void deinitRtspInfo();
private:
    volatile bool m_bThreadStop;
    TALKBACK_THREAD_HANDLE m_tThreadId;
    volatile bool m_bStartTalkback;
    lpTalkbackContext m_pTalkbackContext;
    TalkbackRtsp *m_pRtsp;
    tagTalkbackRtspInfo *m_pRtspInfo;

    tagAudioContext *m_pAudioDataContext;
};

#endif // TALKBACKCORE_H
