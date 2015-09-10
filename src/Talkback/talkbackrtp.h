#ifndef TALKBACKRTP_H
#define TALKBACKRTP_H
#include "sock.h"
#include "talkbackRtpDef.h"
typedef struct __tagTalkbackRtpInfo{
    SOCK_t rtp_sock;
    int rtp_server_port;
    int rtp_client_port;
    int low_transport;	// udp or tcp
    int meida_format;
}tagTalkbackRtpInfo;
class TalkbackRtp
{
public:
    TalkbackRtp();
    ~TalkbackRtp();
    bool init(SOCK_t rtp_sock,int rtp_server_port,int rtp_client_port,int low_transport,int meida_format);
    bool sendbuf();
    void deinit();
private:
    tagTalkbackRtpInfo *m_pRtpInfo;
};

#endif // TALKBACKRTP_H
