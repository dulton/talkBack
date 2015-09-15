#ifndef TALKBACKRTSP_H
#define TALKBACKRTSP_H
#include "sock.h"
#include "talkbackrtspdef.h"
#include "sdplib.h"
#include "authentication.h"
#include "talkbackRtcpDef.h"
#include "talkbackRtpDef.h"
#include "talkbackrtp.h"
#include "talkbackrtcp.h"
#include "TalkBackDataTypeCommon.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct rtsp_socket_group
{
    int rtp_socket;             //rtp
    unsigned short rtp_port;    //rtp
    int rtcp_socket;            //rtcp
    unsigned short rtcp_port;   //rtcp
} RTSP_SOCKET_GROUP;

typedef struct __tagTalkbackRtspInfo{
    int     role;//client ,server
    char    userName[20];
    char    passWord[20];
    int     nPort;//目标端口
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
    uint64_t session_lastTime;//单位秒
    uint64_t audioDataCheckTime;
    unsigned int rtpseq;
    unsigned int rtptime;
    Authentication_t *auth;

    int stream_type; // invalid for rtsp player

    char peername[20];
    int buffer_time;//unit : ms, only valid for rtsp player
    int low_transport;	// udp or tcp
    int cast_type; //unicast or multicast
    int b_interleavedMode;//是否使用 rtsp/rtp混合模式
    int client_port;//rtp 端口
    int server_port;//对方端口
    int channel;
    talkback_int64 startPlayTime;
    uint32_t ssrc;
    int work_mode;//record or play

    enRTP_TRANSPORT transport;

    RtpMapAttr_t    rtpMap;
    tagAudioCodeMode tAudioCodeMode;

    TalkbackRtcp *pRtcp_video;
    TalkbackRtcp *pRtcp_audio;
    TalkbackRtp *pRtp_video;
    TalkbackRtp *pRtp_audio;
    RTSP_SOCKET_GROUP *pSocketGroup;
    fd_set  read_set;
    FILE *file;
}tagTalkbackRtspInfo;
class TalkbackRtsp
{
public:
    TalkbackRtsp();
    ~TalkbackRtsp();
    bool setup(int &nFlag);
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
    bool talkbackRtspPlay(char *control,int n);
    void talkbackRtspTeardown(char *control,int n);
    bool talkbackRtspKeepalive(char *control,int n);
    bool requestSeup(char *control,char *media_type,int type,int real_type);//发送 setup 请求

    bool sendRtspPacket();//发送 rtsp 包
    bool readRtspMessage();//接受 rtsp 包
    bool parseRtspResponse(int *statusCode,char *info);//解析rtsp 包

    bool parseRtspTransport(char *buf);//解析 transport 字段

    bool rtsp_setup_transport(char *buf);//打包 transport 字段

    uint32_t hash_string(char *str);
    //申请可用端口


    bool getSocketGroup(RTSP_SOCKET_GROUP *rsg);
    int getAvailablePort(unsigned short &port);
    int createSocket(int port);
private:
    tagTalkbackRtspInfo *m_pRtspInfo;
};

#endif // TALKBACKRTSP_H
