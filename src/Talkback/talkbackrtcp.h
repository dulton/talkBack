#ifndef TALKBACKRTCP_H
#define TALKBACKRTCP_H
#include "talkbackrtp.h"
#include "talkbackrtspdef.h"
typedef struct __tagTalkbackRtcpInfo{
    SOCK_t rtcp_sock;
    int rtcp_server_port;
    int rtcp_client_port;
    int low_transport;	// udp or tcp
    int     role;//client ,server
    int cast_type; //unicast or multicast
    int b_interleavedMode;//是否使用 rtsp/rtp混合模式
    SOCK_t  rtspSocket;
    uint32_t ssrc;
    TalkbackRtp *pRtp;
}tagTalkbackRtcpInfo;

class TalkbackRtcp
{
public:
    TalkbackRtcp();
    ~TalkbackRtcp();
    bool init(int rtcp_server_port,int rtcp_client_port,int low_transport,int role,int cast_type,int b_interleavedMode,SOCK_t rtspSocket,SOCK_t rtcpSocket,TalkbackRtp *pRtp);
    void deinit();
private:
    int rtcp_init_transport(int cast_type,int protocal,int chn_port);
private:
    tagTalkbackRtcpInfo *m_pRtcpInfo;
};

#endif // TALKBACKRTCP_H
