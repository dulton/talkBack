#ifndef TALKBACKRTSP_H
#define TALKBACKRTSP_H
#include "sock.h"
#include "talkbackrtspdef.h"
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
