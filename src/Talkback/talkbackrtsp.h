#ifndef TALKBACKRTSP_H
#define TALKBACKRTSP_H
#include "sock.h"
#include "talkbackrtspdef.h"
#include "sdplib.h"
#include "authentication.h"
typedef struct __tagTalkbackRtspInfo{
    char    userName[256];
    char    passWord[256];
    int     nPort;
    char    url[256];
    char    ip[20];
    char    streamName[128];
    SOCK_t  rtspSocket;
    char    payload[RTSP_BUF_SIZE +1];
    int     payloadSize;
    int     cseq;
    int     bLogin;		// login success or not
    char    allow_method[128];
    char    agent[128];
    SessionDesc_t *sdp;
    char    session_id[32];
    uint32_t session_timeout;

    unsigned int rtpseq;
    unsigned int rtptime;
    Authentication_t *auth;
}tagTalkbackRtspInfo;
class TalkbackRtsp
{
public:
    TalkbackRtsp();
    ~TalkbackRtsp();
    bool setup();
    bool play();
    bool keepalive();
    void teardown();
    void deinit();
    void init(tagTalkbackRtspInfo *pRtspInfo);
private:
    bool talkbackRtspSetup_connect();
    bool talkbackRtspSetup_option();
    bool talkbackRtspSetup_describe();
    bool talkbackRtspSetup_setup();
    bool sendRtspPacket();
    bool readRtspMessage();
    bool parseRtspResponse(int *statusCode,char *info);
private:
    tagTalkbackRtspInfo *m_pRtspInfo;
};

#endif // TALKBACKRTSP_H
