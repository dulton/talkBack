#include "talkbackrtsp.h"
#include "vlog.h"

#include "TalkBackDataTypeCommon.h"

#include "TalkBackCommonTool.h"


TalkbackRtsp::TalkbackRtsp():m_pRtspInfo(NULL)
{
}

TalkbackRtsp::~TalkbackRtsp()
{

}

static RStatusCode_t rtspRStatusCodes[]={
    {100,"Continue"},					////-0
    {200,"OK"},
    {201,"Created"},
    {250,"Low on Storage Space"},
    {300,"Multiple Choices"},
    {301,"Moved Permanently"},
    {302,"Moved Temporarily"},
    {303,"See Other"},
    {304,"Not MOdified"},
    {305,"Use Proxy"},
    {400,"Bad Request"},				////-10
    {401,"Unauthorized"},
    {402,"Payment Required"},
    {403,"Forbidden"},
    {404,"Not Found"},
    {405,"Method Not Allowed"},
    {406,"Not Acceptable"},
    {407,"Proxy Authentication Required"},
    {408,"Request Time-out"},
    {410,"Gone"},
    {411,"Length Required"},			////-20
    {412,"Precondition Failed"},
    {413,"Request Entity Too Large"},
    {414,"Request-URI Too Large"},
    {415,"Unsupported Media Type"},
    {451,"Parameter Not Understood"},
    {452,"Conference Not Found"},
    {453,"Not Enough Bandwidth"},
    {454,"Session Not Found"},
    {455,"Method Not Valid in This State"},
    {456,"Header Field Not Vaild for Resource"},	////-30
    {457,"Invalid Range"},
    {458,"Parameter Is Read-Only"},
    {459,"Aggregate operation not allowed"},
    {460,"Only aggregate operation allowed"},
    {461,"Unsupported transport"},
    {462,"Destination unreachable"},
    {500,"Internal Server Error"},
    {501,"Not Implemented"},
    {502,"Bad Gateway"},
    {503,"Service Unavailable"},					////-40
    {504,"Gateway Time-out"},
    {505,"RTSP Version not supported"},
    {551,"Option not supported"},					////-43
};
enum{
    RTSP_RSC_CONTINUE = 0,			//// -0
    RTSP_RSC_OK,						////-1
    RTSP_RSC_CREATED,
    RTSP_RSC_LOW_STORAGE,
    RTSP_RSC_MULTI_CHOICES,
    RTSP_RSC_MOVED_PERMANENTLY,		////-5
    RTSP_RSC_MOVED_TEMPORARILY,
    RTSP_RSC_SEE_OTHER,
    RTSP_RSC_NOT_MODIFIED,
    RTSP_RSC_USE_PROXY,
    RTSP_RSC_BAD_REQUEST,			////-10
    RTSP_RSC_UNAUTHORIZED,
    RTSP_RSC_PAYMENT_REQUIRED,
    RTSP_RSC_FORBIDDEN,
    RTSP_RSC_NOT_FOUND,
    RTSP_RSC_METHOD_NOT_ALLOWED,		////-15
    RTSP_RSC_NOT_ACCEPTABLE,
    RTSP_RSC_PROXY_AUTHEN_REQUIRED,
    RTSP_RSC_REQUEST_TIMEOUT,
    RTSP_RSC_GONE,
    RTSP_RSC_LENGTH_REQUIRED,		////-20
    RTSP_RSC_PRECONDITION_FAILED,
    RTSP_RSC_REQUEST_ENTITY_TOOLARGE,
    RTSP_RSC_REQUEST_URI_TOOLARGE,
    RTSP_RSC_UNSUPPORTED_MEDIA,
    RTSP_RSC_PARAMETER_NOT_UNDERSTOOD,	////-25
    RTSP_RSC_CONFERENCE_NOT_FOUND,
    RTSP_RSC_NOT_ENOUGHT_BANDWIDTH,
    RTSP_RSC_SESSION_NOT_FOUND,
    RTSP_RSC_METHOD_NOT_VAILD,
    RTSP_RSC_HEADER_FIELD_NOT_VAILD,		////-30
    RTSP_RSC_INVALID_RANGE,
    RTSP_RSC_PARAMETER_IS_READONLY,
    RTSP_RSC_AGGREGATE_NOT_ALLOWED,
    RTSP_RSC_ONLY_AGGREGATE_ALLOWED,
    RTSP_RSC_UNSUPPORTED_TRANSPORT,		////-35
    RTSP_RSC_DESITIATION_UNREACHABLE,
    RTSP_RSC_INTERNAL_SERVER_ERROR,
    RTSP_RSC_NOT_IMPLEMENTED,
    RTSP_RSC_GAD_GATEWAY,
    RTSP_RSC_SERVICE_UNAVAILABLE,		////-40
    RTSP_RSC_GATEWAY_TIMEOUT,
    RTSP_RSC_RTSP_VERSION_NOTSUPPORTED,
    RTSP_RSC_OPTION_NOTSUPPORTED,
    RTSP_RSC_END							////-44
};
bool TalkbackRtsp::setup()
{
    typedef enum __tagTalkbackRtspSetup{
        tagTalkbackRtspSetup_connect,
        tagTalkbackRtspSetup_option,
        tagTalkbackRtspSetup_describe,
        tagTalkbackRtspSetup_setup,
        tagTalkbackRtspSetup_success,
        tagTalkbackRtspSetup_fail,
        tagTalkbackRtspSetup_exit,
    }tagTalkbackRtspSetup;
    bool bStop=false;
    bool bFlag=false;
    tagTalkbackRtspSetup tStep=tagTalkbackRtspSetup_connect;
    while(bStop==false){
        switch (tStep){
            case tagTalkbackRtspSetup_connect:{
                if(talkbackRtspSetup_connect()){
                    tStep=tagTalkbackRtspSetup_option;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                }
            }
            break;
        case tagTalkbackRtspSetup_option:{
                if(talkbackRtspSetup_option()){
                    tStep=tagTalkbackRtspSetup_describe;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                }
            }
            break;
        case tagTalkbackRtspSetup_describe:{
                if(talkbackRtspSetup_describe()){
                    tStep=tagTalkbackRtspSetup_setup;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                }
            }
            break;
        case tagTalkbackRtspSetup_setup:{
                if(talkbackRtspSetup_setup()){
                    tStep=tagTalkbackRtspSetup_success;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                }
            }
            break;
        case tagTalkbackRtspSetup_success:{
                bFlag=true;
                tStep=tagTalkbackRtspSetup_exit;
            }
            break;
        case tagTalkbackRtspSetup_fail:{
                bFlag=false;
                tStep=tagTalkbackRtspSetup_exit;
            }
            break;
        case tagTalkbackRtspSetup_exit:{
                bStop=true;
            }
            break;
        }
    }
    return bFlag;
}

bool TalkbackRtsp::play()
{

}

bool TalkbackRtsp::keepalive()
{

}

void TalkbackRtsp::teardown()
{
}

void TalkbackRtsp::deinit()
{

}

void TalkbackRtsp::init(tagTalkbackRtspInfo *pRtspInfo)
{
    m_pRtspInfo=pRtspInfo;
}

bool TalkbackRtsp::talkbackRtspSetup_connect()
{
    SOCK_t tSocket=SOCK_tcp_connect2(m_pRtspInfo->ip,m_pRtspInfo->nPort,4000,RTSP_SOCK_TIMEOUT);
    if(-1==tSocket){
        INFO_PRINT("talkbackRtspSetup_connect fail as connect to dst_ip fail");
        return false;
    }else{

    }
    m_pRtspInfo->rtspSocket=tSocket;
    return true;
}

bool TalkbackRtsp::talkbackRtspSetup_option()
{
    int nStatus_code;
    char tmp[256];
    const char format[]=
            "OPTIONS %s %s \r\n"\
            "CSeq: %d\r\n"\
            "User-Agent: %s\r\n"\
            "\r\n";
    sprintf(tmp,"rtsp://%s:%d/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,m_pRtspInfo->streamName);
    sprintf(m_pRtspInfo->payload,format,tmp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT);
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
    VLOG(VLOG_DEBUG,"request (size:%d):\r\n%s\r\n",m_pRtspInfo->payloadSize,m_pRtspInfo->payload);

    if(sendRtspPacket()==false){
        VLOG(VLOG_DEBUG,"(file:%s),(line:%d)sendRtspPacket  fail:%s\r\n",__func__,__LINE__,m_pRtspInfo->payload);
        return false;
    }
    if(readRtspMessage()==false){
        VLOG(VLOG_DEBUG,"(file:%s),(line:%d)readRtspMessage  fail:%s\r\n",__func__,__LINE__,m_pRtspInfo->payload);
        return false;
    }
    if(parseRtspResponse(&nStatus_code,tmp)==false){
        VLOG(VLOG_DEBUG,"(file:%s),(line:%d)parseRtspResponse  fail:%s\r\n",__func__,__LINE__,m_pRtspInfo->payload);
        return false;
    }
    return true;
}

bool TalkbackRtsp::talkbackRtspSetup_describe()
{

}

bool TalkbackRtsp::talkbackRtspSetup_setup()
{

}

bool TalkbackRtsp::sendRtspPacket()
{
    fd_set wset;
    int nRet;
    struct timeval tTimeOut;
    char *pPayload=m_pRtspInfo->payload;
    int nRemind=m_pRtspInfo->payloadSize;
    while (nRemind) {
        tTimeOut.tv_sec=3;
        tTimeOut.tv_usec=0;
        FD_ZERO(&wset);
        FD_SET(m_pRtspInfo->rtspSocket,&wset);
        nRet=select(m_pRtspInfo->rtspSocket+1,NULL,&wset,NULL,&tTimeOut);
        if(nRet>0){
            if(FD_ISSET(m_pRtspInfo->rtspSocket,&wset)){
                nRet=send(m_pRtspInfo->rtspSocket,pPayload,nRemind,0);
                if(nRet<0){
                    if(SOCK_ERR==SOCK_EINTR){
                        VLOG(VLOG_WARNING,"RTSP SEND errno:%d retry!\n",SOCK_ERR);
                        continue;
                    }else{
                        goto ERR_EXIT;
                    }
                }else{
                    pPayload+=nRet;
                    nRemind-=nRet;
                }
            }else{
                goto ERR_EXIT;
            }
        }else{
            goto ERR_EXIT;
        }
    }
    VLOG(VLOG_DEBUG,"rtsp send packet(size:%d) ok",m_pRtspInfo->payloadSize);
    return true;
ERR_EXIT:
    VLOG(VLOG_ERROR,"rtsp send packet(size:%d) failed.",m_pRtspInfo->payloadSize);
    return false;
}
char *STRCASESTR(char *s1,char *s2)
{
    char *ptr = s1;

    if (!s1 || !s2 || !*s2) return s1;

    while (*ptr) {
        if (toupper(*ptr) == toupper(*s2)) {
            char * cur1 = ptr + 1;
            char * cur2 = s2 + 1;
            while (*cur1 && *cur2 && toupper(*cur1) == toupper(*cur2)) {
                cur1++;
                cur2++;
            }
            if (!*cur2) {
                return ptr;
            }
        }
        ptr++;
    }
    return NULL;
}
static inline bool http_get_number(char *src,char *key,int *ret){
    char *temp=STRCASESTR(src,key);
    if(temp==NULL){
        *ret=-1;
        return false;
    }else{
        temp+=strlen(key);
        if((*temp)==' '){
            temp++;
        }
        sscanf(temp,"%d",ret);
        return true;
    }
}
static inline bool http_get_string(char *src,char *key,char *ret){
    char *temp=STRCASESTR(src,key);
    if(NULL==temp){
        *ret=0;
        return false;
    }else{
        temp+=strlen(key);
        if(*temp == ' '){
            temp++;
        }
        sscanf(temp,"%[^\r\n]",ret);
        return true;
    }
}
bool TalkbackRtsp::readRtspMessage()
{
    char *pEndPoint=m_pRtspInfo->payload;
    char *pTemp=NULL;
    int nRevice,nReadedSize=0,nExpectSize=1;
    int nContext_len=0;
    int nPacket_size=-1;
    do{
        if(nReadedSize+nExpectSize>RTSP_BUF_SIZE){
            VLOG(VLOG_ERROR,"expect rtsp buffer size out of range,readed:%d expected:%d",nReadedSize,nExpectSize);
            return false;
        }
        nRevice=recv(m_pRtspInfo->rtspSocket,pEndPoint,nExpectSize,0);
        if(nReadedSize<0){
            if(SOCK_ERR==SOCK_EINTR){
                VLOG(VLOG_WARNING,"tcp recv error SOCK_EINTR");
                continue;
            }else if(SOCK_ERR==SOCK_EAGAIN){
                VLOG(VLOG_ERROR,"tcp recv SOCK_EAGAIN in nonblocking mode");
                return false;
            }else if(SOCK_ERR==SOCK_ETIMEOUT){
                VLOG(VLOG_ERROR,"tcp recv time out");
                return false;
            }else{
                VLOG(VLOG_ERROR,"tcp recv unkonw error :@%d ###",SOCK_ERR);
                return false;
            }
        }else if(nRevice==0){
            VLOG(VLOG_DEBUG,"network is shutdown by peer");
            return false;
        }else{
            //keep going
        }
        pEndPoint[nRevice]=0;
        nReadedSize+=nRevice;
        VLOG(VLOG_DEBUG,"nRevice:%d,nReadedSize:%d,nExpectSize:%d,nPacket_size:%d,nContext_len:%d",
             nRevice,nReadedSize,nExpectSize,nPacket_size,nContext_len);
        if(nReadedSize==nPacket_size){
            break;
        }
        if(m_pRtspInfo->payload[0]==RTSP_INTERLEAVED_MAGIC){
            RtspInterHeader_t *pInterHeader=NULL;
            if(nReadedSize<sizeof(RtspInterHeader_t)){
                nExpectSize=sizeof(RtspInterHeader_t)-nReadedSize;
            }else{
                pInterHeader=(RtspInterHeader_t *)m_pRtspInfo->payload;
                nPacket_size=ntohs(pInterHeader->length)+sizeof(RtspInterHeader_t);
                if(nReadedSize<nPacket_size){
                    nExpectSize=nPacket_size-nReadedSize;
                }else if(nReadedSize==nPacket_size){
                    break;
                }else{
                    VLOG(VLOG_ERROR,"ocurr unhandle error,please check it");
                    return false;
                }
            }
        }else if((unsigned char )m_pRtspInfo->payload[0]>=0x81){// zhongwei NVR specific heartbreak
            nPacket_size=20;
            nExpectSize=nPacket_size-nReadedSize;
        }else{//rtsp message
            if(http_get_number(m_pRtspInfo->payload,"Content-length:",&nContext_len)==false){//without content
                if(strstr(pEndPoint,"\r\n\r\n")!=NULL){
                    break;
                }else{
                    nExpectSize=RTSP_BUF_SIZE-nReadedSize-1;
                }
            }else{
                if((pTemp=strstr(pEndPoint,"\r\n\r\n"))!=NULL){
                    nPacket_size=nContext_len+(pTemp-m_pRtspInfo->payload)+4;
                    if(nReadedSize==nPacket_size){
                        break;
                    }else{
                        nExpectSize=nPacket_size-nReadedSize;
                    }
                }else{
                    nExpectSize=RTSP_BUF_SIZE-nReadedSize-1;
                }
            }
        }
        pEndPoint+=nRevice;
    }while(1);
    m_pRtspInfo->payload[nReadedSize]=0;
    m_pRtspInfo->payloadSize=nReadedSize;
    VLOG(VLOG_DEBUG,"read rtsp packet done,size:%d",nReadedSize);
    if(m_pRtspInfo->payload[0]!=RTSP_INTERLEAVED_MAGIC){
        VLOG(VLOG_DEBUG,"payload:\r\n:%s",m_pRtspInfo->payload);
    }
    return true;
}

bool TalkbackRtsp::parseRtspResponse(int *statusCode, char *info)
{
    int nCseq;
    char temp[256];
    char *ptrSdp=NULL;
    char *ptrRtp=NULL;
    if(memcmp(m_pRtspInfo->payload,RTSP_VERSION,strlen(RTSP_VERSION))==0){
        sscanf(m_pRtspInfo->payload,"%*s %d %s",statusCode,info);
        VLOG(VLOG_DEBUG,"response code :%d info:%s",*statusCode,info);
        if((*statusCode)==rtspRStatusCodes[RTSP_RSC_UNAUTHORIZED].code){
           //auth_init
            m_pRtspInfo->bLogin=false;
        }else if((*statusCode)!=rtspRStatusCodes[RTSP_RSC_OK].code){
            // no ok
            VLOG(VLOG_ERROR,"response code not ok ,%d",*statusCode);
            return false;
        }else{
            //keep going
        }
    }
    //check cseq
    if(http_get_number(m_pRtspInfo->payload,"CSeq:",&nCseq)==false){
        VLOG(VLOG_ERROR,"invaild response format, not found cseq");
        return false;
    }else{
        if(nCseq!=m_pRtspInfo->cseq){
            VLOG(VLOG_ERROR,"cseq number is wrong");
            return false;
        }else{
            //keep going
        }
    }

    if(http_get_string(m_pRtspInfo->payload,"Public:",temp)==true){
        strcpy(m_pRtspInfo->allow_method,temp);
    }
    if(http_get_string(m_pRtspInfo->payload,"Server:",temp)==true){
        strncpy(m_pRtspInfo->agent,temp,sizeof(m_pRtspInfo->agent));
    }
    if(http_get_string(m_pRtspInfo->payload,"User-Agent:",temp)==true){
        strncpy(m_pRtspInfo->agent,temp,sizeof(m_pRtspInfo->agent));
    }
    if(http_get_string(m_pRtspInfo->payload,"Content-type:",temp)==true){
        if(strcmp(temp,SDP_MEDIA_TYPE)==0){
            VLOG(VLOG_DEBUG,"get sdp,goto parse it");
            ptrSdp=strstr(m_pRtspInfo->payload,"\r\n\r\n");
            if(ptrSdp==NULL){
                VLOG(VLOG_ERROR,"decribe response format error,check it");
                return false;
            }
            ptrSdp+=strlen("\r\n\r\n");
            m_pRtspInfo->sdp=SDP_decode(ptrSdp);
            if(m_pRtspInfo->sdp==NULL){
                return false;
            }
        }else{
            VLOG(VLOG_DEBUG,"\t undefine content-type:%s",temp);
        }
    }
    if(http_get_string(m_pRtspInfo->payload,"Session:",temp)==true){
        if(strstr(temp,";")!=NULL){
            sscanf(temp,"%[^;];timeout=%d",m_pRtspInfo->session_id,&m_pRtspInfo->session_timeout);
        }else{
            strcpy(m_pRtspInfo->session_id,temp);
        }
        VLOG(VLOG_DEBUG,"\t session id:%s",m_pRtspInfo->session_id);
    }
    if(http_get_string(m_pRtspInfo->payload,"RTP-Info:",temp)==true){
        if((ptrRtp=strstr(temp,"seq="))!=NULL){
            ptrRtp+=strlen("seq=");
            sscanf(ptrRtp,"%u",&m_pRtspInfo->rtpseq);
        }else{
            m_pRtspInfo->rtpseq=0;
        }
        if((ptrRtp=strstr(temp,"rtptime="))!=NULL){
            ptrRtp += strlen("rtptime=");
            sscanf(ptrRtp,"%u",&m_pRtspInfo->rtptime);
        }else{
            m_pRtspInfo->rtptime=0;
        }
        VLOG(VLOG_DEBUG,"\t rtp seq: %u rtptime:%u",m_pRtspInfo->rtpseq,m_pRtspInfo->rtptime);
    }
    //auth
    if(http_get_string(m_pRtspInfo->payload,"WWW-Authenticate:",temp)==true){
        if(HTTP_AUTH_client_init(&m_pRtspInfo->auth,temp)==AUTH_RET_FAIL){
            VLOG(VLOG_ERROR,"\t WWW-Authenticate parse fail:%s",temp);
            return false;
        }
    }
    VLOG(VLOG_DEBUG,"parse response success");
    return true;
}



