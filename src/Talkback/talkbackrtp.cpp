#include "talkbackrtp.h"
#include "TalkBackDataTypeCommon.h"

TalkbackRtp::TalkbackRtp():m_pRtpInfo(NULL)
{
    m_pRtpInfo=new tagTalkbackRtpInfo;
    m_pRtpInfo->rtp_sock=-1;
}

TalkbackRtp::~TalkbackRtp()
{

}

bool TalkbackRtp::init(SOCK_t rtp_sock, int rtp_server_port, int rtp_client_port, int low_transport, int meida_format)
{
    if(m_pRtpInfo!=NULL){
        m_pRtpInfo->rtp_sock=rtp_sock;
        m_pRtpInfo->rtp_server_port=rtp_server_port;
        m_pRtpInfo->rtp_client_port=rtp_client_port;
        m_pRtpInfo->low_transport=low_transport;
        m_pRtpInfo->meida_format=meida_format;
        return true;
    }else{
        return false;
    }
}



bool TalkbackRtp::sendbuf()
{

}

void TalkbackRtp::deinit()
{
    //fix me
}
