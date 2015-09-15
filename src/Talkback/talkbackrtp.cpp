#include "talkbackrtp.h"
#include "TalkBackDataTypeCommon.h"
#include "TalkBackCommonTool.h"
#include "vlog.h"
TalkbackRtp::TalkbackRtp():m_pRtpInfo(NULL),
    m_pRtp(NULL)
{
    m_pRtpInfo=new tagTalkbackRtpInfo;
    memset(m_pRtpInfo->peername,0,sizeof(m_pRtpInfo->peername));
    m_pRtpInfo->rtp_sock=-1;

}

TalkbackRtp::~TalkbackRtp()
{
    if(m_pRtpInfo!=NULL){
        delete m_pRtpInfo;
        m_pRtpInfo=NULL;
    }
    deinitRtpHeader();
}

bool TalkbackRtp::init(SOCK_t rtp_sock, int rtp_server_port, int rtp_client_port,
                       int low_transport, int media_format,char *dstIp)
{
    if(m_pRtpInfo!=NULL){
        m_pRtpInfo->rtp_sock=rtp_sock;
        m_pRtpInfo->rtp_server_port=rtp_server_port;
        m_pRtpInfo->rtp_client_port=rtp_client_port;
        m_pRtpInfo->low_transport=low_transport;
        m_pRtpInfo->media_format=media_format;
        memcpy(m_pRtpInfo->peername,dstIp,strlen(dstIp));
        m_nDstPort=rtp_server_port;
        if(initRtpHeader()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}



bool TalkbackRtp::sendbuf(char *src,uint32_t len,uint32_t ts)
{

    char (*buffer)[RTP_PACKET_SIZE]=(char (*)[RTP_PACKET_SIZE])NULL;

    if(mallocSendBuff()==false){
        INFO_PRINT("sendbuf fail as mallocSendBuff fail");
        return false;
    }

    buffer=(char(*)[RTP_PACKET_SIZE])m_pRtp->packet.buffer;

    if(packSendBuff(src,len,ts)==false){
        INFO_PRINT("sendbuf fail as packSendBuff fail");
        return false;
    }
    int bRet=false;
    for(int i=0;i<m_pRtp->packet.cnt;i++){
        if(m_pRtp->interleaved==false){
            bRet=SOCK_sendto(m_pRtp->sock,m_pRtp->peername,m_pRtp->peer_chn_port,buffer[i],m_pRtp->packet.buf_size[i]);
        }else{
            bRet=SOCK_send(m_pRtp->sock,buffer[i],m_pRtp->packet.buf_size[i]);
        }
        if(bRet==RET_FAIL){
            INFO_PRINT("sendbuf fail as SOCK_sendto fail");
            return false;
        }
    }
    return true;
}

void TalkbackRtp::deinit()
{
    //fix me
    deinitRtpHeader();
}

tagTalkbackRtpInfo *TalkbackRtp::getRtpInfo()
{
    return m_pRtpInfo;
}

bool TalkbackRtp::initRtpHeader()
{
    deinitRtpHeader();
    RtpPacket_t *pPacket_t=NULL;
    RtpHeader_t *pRtpHeader_t=NULL;
    RtspInterHeader_t *pRtspInterHeader_t=NULL;
    m_pRtp=(Rtp_t*)malloc(sizeof(Rtp_t));
    if(m_pRtp==NULL){
        INFO_PRINT("initRtpHeader fail as m_pRtp malloc fail");
        return false;
    }
    memset(m_pRtp,0,sizeof(Rtp_t));
    pPacket_t=&m_pRtp->packet;
    pRtpHeader_t=&m_pRtp->header;
    pRtspInterHeader_t=&m_pRtp->interHeader;

    memset(m_pRtp->peername,0,sizeof(m_pRtp->peername));
    m_pRtp->role=RTP_SERVER;
    m_pRtp->timestamp=0xffffffff;
    m_pRtp->seq=0;
    m_pRtp->raw_data=false;
    m_pRtp->interleaved=false;

    m_pRtp->base_seq=1;
    m_pRtp->cycle_cnt=0;
    m_pRtp->packet_cnt=0;
    m_pRtp->fraction_lost=0;
    m_pRtp->comulative_lost=0;

    pPacket_t->cnt=0;
    pPacket_t->malloc_size=0;
    pPacket_t->buffer=NULL;

    //init rtp header
    pRtpHeader_t->version= RTP_VERSION;
    pRtpHeader_t->padding =0;
    pRtpHeader_t->extension=0;
    pRtpHeader_t->csrc_cnt=0;
    pRtpHeader_t->marker=0;
    pRtpHeader_t->payload_type=0;
    pRtpHeader_t->timestamp =0;
    pRtpHeader_t->ssrc=htonl(m_uiSsrc);
    if(m_pRtp->interleaved==true){
        pRtspInterHeader_t->magic='$';
        pRtspInterHeader_t->channel=m_nDstPort;
        pRtspInterHeader_t->length=0;
    }else{
        memset(pRtspInterHeader_t,0,sizeof(RtspInterHeader_t));
    }
    m_pRtp->sock=m_pRtpInfo->rtp_sock;
    strcpy(m_pRtp->peername,m_pRtpInfo->peername);
    m_pRtp->peer_chn_port=m_pRtpInfo->rtp_server_port;
    return true;
}

void TalkbackRtp::deinitRtpHeader()
{
    if(m_pRtp==NULL){
        return;
    }
    if(NULL!=m_pRtp->packet.buffer){
        if(m_pRtp->role==RTP_SERVER){
            free(m_pRtp->packet.buffer);
        }else{
            //fix me
        }
            m_pRtp->packet.buffer=NULL;
    }
    free(m_pRtp);
    m_pRtp=NULL;
}

bool TalkbackRtp::rtp_packet_g711_A(char *src, uint32_t len, uint32_t ts)
{
    return rtp_packet_g711(src,len,ts,RTP_TYPE_PCMA);
}

bool TalkbackRtp::rtp_packet_g711_U(char *src, uint32_t len, uint32_t ts)
{
    return rtp_packet_g711(src,len,ts,RTP_TYPE_PCMU);
}

bool TalkbackRtp::rtp_packet_g711(char *src, uint32_t len, uint32_t ts, int type)
{
    char *ptr=NULL;
    RtpHeader_t *pRtpHeader=(RtpHeader_t *)&m_pRtp->header;
    RtpPacket_t *pRtpPacket=&m_pRtp->packet;
    int ex_header_size=(m_pRtp->interleaved==false)?0:4;
    char (*buffer)[RTP_PACKET_SIZE]=(char (*)[RTP_PACKET_SIZE])m_pRtp->packet.buffer;
    if(sizeof(RtpHeader_t)+len+ex_header_size>RTP_PACKET_SIZE){
        VLOG(VLOG_ERROR,"thre buffer out of range");
        return false;
    }
    m_pRtp->timestamp=ts;
    pRtpHeader->timestamp=htonl(m_pRtp->timestamp);
    pRtpPacket->cnt=1;
    ptr=buffer[0];
    if(m_pRtp->interleaved!=false){
        m_pRtp->interHeader.length=htons((unsigned short)(sizeof(RtpHeader_t)+len));
        memcpy(ptr,&m_pRtp->interHeader,sizeof(RtspInterHeader_t));
        ptr+=sizeof(RtspInterHeader_t);
    }

    m_pRtp->header.payload_type=type;
    m_pRtp->header.marker=1;
    m_pRtp->header.sequence_number=htons((unsigned short)(++m_pRtp->seq));
    memcpy(ptr,pRtpHeader,sizeof(RtpHeader_t));
    ptr+=sizeof(RtpHeader_t);
    memcpy(ptr,src,len);
    pRtpPacket->buf_size[0]=sizeof(RtpHeader_t)+len+ex_header_size;
    return true;
}

bool TalkbackRtp::mallocSendBuff()
{
    uint32_t expect_size=0;
    expect_size=RTP_MAX_FRAGMENTATION*RTP_PACKET_SIZE;
    if(m_pRtp==NULL){
        INFO_PRINT("sendbuf fail as m_pRtp is NULL");
        return false;
    }
    if(m_pRtp->packet.buffer==NULL){
        m_pRtp->packet.buffer=malloc(expect_size);
        if(m_pRtp->packet.buffer==NULL){
            return false;
        }
        m_pRtp->packet.malloc_size=expect_size;
    }else if(m_pRtp->packet.malloc_size<expect_size){
        m_pRtp->packet.buffer=realloc(m_pRtp->packet.buffer,expect_size);
        if(NULL==m_pRtp->packet.buffer){
            return false;
        }else{
            m_pRtp->packet.malloc_size=expect_size;
        }
    }
    return true;
}

bool TalkbackRtp::packSendBuff(char *src, uint32_t len, uint32_t ts)
{
    bool bRet=false;
    if(m_pRtpInfo->media_format==RTP_TYPE_PS){
        VLOG(VLOG_ERROR,"unsupport stream type:%d",m_pRtpInfo->media_format);
        return false;
    }else if(m_pRtpInfo->media_format==RTP_TYPE_PCMA){
        bRet=rtp_packet_g711_A(src,len,ts);
    }else if(m_pRtpInfo->media_format==RTP_TYPE_PCMU){
        bRet=rtp_packet_g711_U(src,len,ts);
    }else if(m_pRtpInfo->media_format==RTP_TYPE_DYNAMIC){
        VLOG(VLOG_ERROR,"unsupport stream type:%d",m_pRtpInfo->media_format);
        return false;
    }else{
        VLOG(VLOG_ERROR,"unsupport stream type:%d",m_pRtpInfo->media_format);
        return false;
    }
    if(bRet==false){
        VLOG(VLOG_ERROR,"send buffer fail as rtp_packet fail");
        return false;
    }
    return true;
}



