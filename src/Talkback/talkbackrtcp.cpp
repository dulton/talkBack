#include "talkbackrtcp.h"

#include "vlog.h"
TalkbackRtcp::TalkbackRtcp()
{
    m_pRtcpInfo=new tagTalkbackRtcpInfo;
    m_pRtcpInfo->pRtp=NULL;
    m_pRtcpInfo->rtcp_sock=-1;
    m_pRtcpInfo->rtspSocket=-1;
}

bool TalkbackRtcp::init(int rtcp_server_port, int rtcp_client_port, int low_transport, int role, int cast_type, int b_interleavedMode, SOCK_t rtspSocket, TalkbackRtp *pRtp)
{
    if(NULL!=m_pRtcpInfo){
        if(b_interleavedMode==true){
            m_pRtcpInfo->rtcp_sock=rtspSocket;
        }else{
            m_pRtcpInfo->rtcp_sock=rtcp_init_transport(cast_type,low_transport,(role==RTSP_SERVER) ? rtcp_server_port : rtcp_client_port);
        }
        m_pRtcpInfo->b_interleavedMode=b_interleavedMode;
        m_pRtcpInfo->rtcp_client_port=rtcp_client_port;
        m_pRtcpInfo->rtcp_server_port=rtcp_server_port;
        m_pRtcpInfo->low_transport=low_transport;
        m_pRtcpInfo->role;
        m_pRtcpInfo->cast_type=cast_type;
        m_pRtcpInfo->rtspSocket=rtspSocket;
        m_pRtcpInfo->pRtp=pRtp;
    }else{
        return false;
    }
}

void TalkbackRtcp::deinit()
{

}

int TalkbackRtcp::rtcp_init_transport(int cast_type, int protocal, int chn_port)
{
    int sock=-1;
    if(protocal == RTP_TRANSPORT_UDP && cast_type==RTP_UNICAST){
        sock=SOCK_udp_init(NULL, chn_port,RTSP_SOCK_TIMEOUT);
    }else if(protocal == RTP_TRANSPORT_TCP && cast_type==RTP_UNICAST){
        VLOG(VLOG_DEBUG,"rtsp over tcp");
    }else if(protocal == RTP_TRANSPORT_UDP && cast_type==RTP_MULTICAST){
        VLOG(VLOG_ERROR,"unsupport transport: %s,%s",(protocal == RTP_TRANSPORT_TCP) ? "tcp" : "udp",
            (cast_type==RTP_MULTICAST) ? "multicast" : "unicast");
    }else{
        VLOG(VLOG_ERROR,"unsupport transport: %s,%s",(protocal == RTP_TRANSPORT_TCP) ? "tcp" : "udp",
            (cast_type==RTP_MULTICAST) ? "multicast" : "unicast");
    }
    return sock;
}
