/*
 *Gateslu
 *2013-08-28
 *AVTrace
 */

#ifndef AVT_RTSPSOCKET_H
#define AVT_RTSPSOCKET_H

typedef struct rtsp_socket_group
{
    int rtp_socket;             //rtp
    unsigned short rtp_port;    //rtp
    int rtcp_socket;            //rtcp
    unsigned short rtcp_port;   //rtcp
} RTSP_SOCKET_GROUP;

class AVT_RTSPSocket
{
public:
    AVT_RTSPSocket();
    static bool GetSocketGroup(RTSP_SOCKET_GROUP *rsg);
    static void FreeSocketGroup(RTSP_SOCKET_GROUP *rsg);
    static int GetAvaliablePort(unsigned short &port);
    static int CreateSocket(int port);
    static bool SetSocketRecvBufSize(int fd, unsigned int requestedSize);
    static bool ConnectTohost(unsigned int svrip, int fd, unsigned short port);
};

#endif // AVT_RTSPSOCKET_H
