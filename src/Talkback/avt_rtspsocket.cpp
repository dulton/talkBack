#include "avt_rtspsocket.h"
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "locker.h"

#ifndef SETNONBLOCK
#define SETNONBLOCK(s) fcntl(s,F_SETFL,O_NONBLOCK)
#endif

static Locker g_getPortLock;

/* @brief 获取可用的端口
 *
 * @param port : 输出，返回可用的端口号
 *
 * @return 若成功则返回true，否则放回false
 */
int AVT_RTSPSocket::GetAvaliablePort(unsigned short &port)
{
    g_getPortLock.lock();
    bool result = true;
    struct sockaddr_in connAddr;
    socklen_t len = sizeof(struct sockaddr_in);

    // 1. 创建一个socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); /* create a socket */

    // 2. 创建一个sockaddr，并将它的端口号设为0
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 0;        // 若port指定为0,则调用bind时，系统会为其指定一个可用的端口号

    // 3. 绑定
    int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));

    if (0 != ret) {
        result = false;
        goto END;
    }

    if (SETNONBLOCK(sockfd) != 0)
    {
        close(sockfd);
        return -1;
    }

    // 4. 利用getsockname获取
    ret = getsockname(sockfd, (struct sockaddr *)&connAddr, &len);

    if (0 != ret){
        result = false;
        goto END;
    }

    port = ntohs(connAddr.sin_port); // 获取端口号

END:
    if (0 == close(sockfd))
    {
        sockfd = -1;
        sockfd = AVT_RTSPSocket::CreateSocket(port);
        if (sockfd == -1)
        {
            close(sockfd);
            result = false;
        }
    }
    else
        result = false;

    g_getPortLock.unlock();

    return sockfd;
}

int AVT_RTSPSocket::CreateSocket(int port)
{
    int sockfd = -1;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
    /* init servaddr */
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    /* bind address and port to socket */
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1)
    {
        ::close(sockfd);
        return -1;
    }

    if (SETNONBLOCK(sockfd) != 0)
    {
        ::close(sockfd);
        return -1;
    }
    return sockfd;
}

bool AVT_RTSPSocket::SetSocketRecvBufSize(int fd, unsigned int requestedSize)
{
    if( setsockopt(fd, SOL_SOCKET, SO_RCVBUF,
                   (char*)&requestedSize,
                   sizeof(requestedSize) ) >= 0)
    {
        return true;
    }
    return false;
}

bool AVT_RTSPSocket::ConnectTohost(unsigned int svrip, int fd, unsigned short port)
{
    struct sockaddr_in			addr_in;
    memset( &addr_in, 0, sizeof(addr_in) );
    addr_in.sin_family	= AF_INET;
    addr_in.sin_addr.s_addr = svrip;
    addr_in.sin_port = htons(port);
    if( connect(fd, (struct sockaddr*)&addr_in, sizeof(addr_in) ) )
    {
        return false;
    }

    return true;
}

AVT_RTSPSocket::AVT_RTSPSocket()
{
}

bool AVT_RTSPSocket::GetSocketGroup(RTSP_SOCKET_GROUP *rsg)
{
    if (!rsg)
        return false;

    int rtpSocket = -1;
    unsigned short rtpPort = 0;
    int rtcpSocket = -1;

    bool ret = false;

    while (1)
    {
        int recvBufSize = 1024*1024*1;
        rtpSocket = GetAvaliablePort(rtpPort);
        if (rtpSocket == -1)
            continue;

        if (!SetSocketRecvBufSize(rtpSocket, recvBufSize))
        {
            close(rtpSocket);
            continue;
        }

        if ((rtpPort&1) != 0)
        {
            close(rtpSocket);
            continue;
        }

        rtcpSocket = CreateSocket(rtpPort+1);
        if (rtcpSocket == -1)
        {
            close(rtpSocket);
            continue;
        }
        ret = true;
        break;
    }

    if (ret)
    {
        rsg->rtp_socket = rtpSocket;
        rsg->rtp_port = rtpPort;
        rsg->rtcp_socket = rtcpSocket;
        rsg->rtcp_port = rtpPort+1;
    }

    return ret;
}

void AVT_RTSPSocket::FreeSocketGroup(RTSP_SOCKET_GROUP *rsg)
{
    if (!rsg)
        return;

    if (rsg->rtp_socket > 0)
        close(rsg->rtp_socket);
    if (rsg->rtp_socket > 0)
        close(rsg->rtcp_socket);
    rsg->rtp_socket = -1;
    rsg->rtcp_socket = -1;
}




