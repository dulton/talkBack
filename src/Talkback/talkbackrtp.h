#ifndef TALKBACKRTP_H
#define TALKBACKRTP_H
#include "sock.h"
#include "talkbackRtpDef.h"
#include "talkbackrtspdef.h"
typedef struct __tagTalkbackRtpInfo{
    SOCK_t rtp_sock;
    int rtp_server_port;
    int rtp_client_port;
    int low_transport;	// udp or tcp
    int media_format;
    char peername[20];

}tagTalkbackRtpInfo;
class TalkbackRtp
{
public:
    TalkbackRtp();
    ~TalkbackRtp();
    bool init(SOCK_t rtp_sock,int rtp_server_port,int rtp_client_port,int low_transport,
              int media_format,char *dspIp);
    bool sendbuf(char *src,uint32_t len,uint32_t ts);
    void deinit();
    tagTalkbackRtpInfo *getRtpInfo();
private:
    bool initRtpHeader();
    void deinitRtpHeader();
    bool rtp_packet_g711_A(char *src,uint32_t len,uint32_t ts);
    bool rtp_packet_g711_U(char *src,uint32_t len,uint32_t ts);
    bool rtp_packet_g711(char *src,uint32_t len,uint32_t ts ,int type);

    bool mallocSendBuff();
    bool packSendBuff(char *src,uint32_t len,uint32_t ts);
private:
    tagTalkbackRtpInfo *m_pRtpInfo;
    Rtp_t *m_pRtp;
    uint32_t m_uiSsrc;
    int m_nDstPort;
};

#endif // TALKBACKRTP_H
