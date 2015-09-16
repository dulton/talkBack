#include "talkbackrtsp.h"
#include "vlog.h"

#include "TalkBackDataTypeCommon.h"

#include "TalkBackCommonTool.h"
#include "talkbackRtpDef.h"
#include "talkbackthread.h"
#ifdef WIN32
#else
#include <ctype.h>
#endif
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
bool TalkbackRtsp::setup(int &nFlags)
{
    //0:对方设备不在线
    //1:对方设备不支持语音回传功能
    //2:成功
    //3:失败
    nFlags=3;
    typedef enum __tagTalkbackRtspSetup{
        tagTalkbackRtspSetup_connect,
        tagTalkbackRtspSetup_option,
        tagTalkbackRtspSetup_describe,
        tagTalkbackRtspSetup_setup,
        tagTalkbackRtspSetup_success,
        tagTalkbackRtspSetup_fail,
        tagTalkbackRtspSetup_exit,
    }tagTalkbackRtspSetup;
    if(m_pRtspInfo==NULL){
        nFlags=3;
        return false;
    }
    bool bStop=false;
    bool bFlag=false;
    tagTalkbackRtspSetup tStep=tagTalkbackRtspSetup_connect;
    while(bStop==false){
        switch (tStep){
            case tagTalkbackRtspSetup_connect:{
                if(talkbackRtspSetup_connect()){
                    tStep=tagTalkbackRtspSetup_option;
                    nFlags=1;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                    nFlags=0;
                    INFO_PRINT("setup fail as talkbackRtspSetup_connect fail");
                }
            }
            break;
        case tagTalkbackRtspSetup_option:{
                if(talkbackRtspSetup_option()){
                    tStep=tagTalkbackRtspSetup_describe;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                    INFO_PRINT("setup fail as talkbackRtspSetup_option fail");
                }
            }
            break;
        case tagTalkbackRtspSetup_describe:{
                if(talkbackRtspSetup_describe()){
                    tStep=tagTalkbackRtspSetup_setup;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                    INFO_PRINT("setup fail as talkbackRtspSetup_describe fail");
                }
            }
            break;
        case tagTalkbackRtspSetup_setup:{
                if(talkbackRtspSetup_setup()){

                    tStep=tagTalkbackRtspSetup_success;
                }else{
                    tStep=tagTalkbackRtspSetup_fail;
                    INFO_PRINT("setup fail as talkbackRtspSetup_setup fail");
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
    if(bFlag){
        nFlags=2;
    }
    return bFlag;
}

bool TalkbackRtsp::play()
{
    //
    if(NULL==m_pRtspInfo){
        INFO_PRINT("play fail as m_pRtspInfo is null");
        return false;
    }
    int nPlayNum=0;
    for(int n=0;n<m_pRtspInfo->sdp->media_num;n++){
        if(m_pRtspInfo->sdp->media[n].bRtspSetUp!=1){
            continue;
        }else{
            //go to play
            Attribute_t attr;
            if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[n].media_n.type,
                                  SDP_ATTR_CONTROL,(void*)&attr,n)==RTSP_RET_FAIL){
                VLOG(VLOG_ERROR,"get media audio attr fail");
                continue;
            }
            if(talkbackRtspPlay(attr.value,n)==true){
                nPlayNum++;
            }else{
                INFO_PRINT("play fail as talkbackRtspPlay fail");
                return false;
            }
        }
    }
    if(nPlayNum==0){
        return false;
    }else{
        return true;
    }
}

bool TalkbackRtsp::keepalive()
{
    if(m_pRtspInfo==NULL){
        return false;
    }
    for(int n=0;n<m_pRtspInfo->sdp->media_num;n++){
        if(m_pRtspInfo->sdp->media[n].bRtspSetUp==1){
            Attribute_t attr;
            if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[n].media_n.type,
                                  SDP_ATTR_CONTROL,(void*)&attr,n)==RTSP_RET_FAIL){
                VLOG(VLOG_ERROR,"get media audio attr fail");
                continue;
            }
            if(talkbackRtspKeepalive(attr.value,n)==false){
                return false;
            }
        }else{
            continue;
        }
    }
    return true;
}

void TalkbackRtsp::teardown()
{
    if(m_pRtspInfo==NULL){
        return ;
    }
    for(int n=0;n<m_pRtspInfo->sdp->media_num;n++){
        if(m_pRtspInfo->sdp->media[n].bRtspSetUp==1){
            Attribute_t attr;
            if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[n].media_n.type,
                                  SDP_ATTR_CONTROL,(void*)&attr,n)==RTSP_RET_FAIL){
                VLOG(VLOG_ERROR,"get media audio attr fail");
                continue;
            }
            talkbackRtspTeardown(attr.value,n);
        }else{
            continue;
        }
    }
}

void TalkbackRtsp::deinit()
{
    m_pRtspInfo=NULL;
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
    int nStatusCode;
    char temp[256];
    char url[200];
    char szAuth[512];
    bool bAuthFlag=false;
    const char format1[]=
            "DESCRIBE %s %s\r\n"\
            "CSeq: %d\r\n"\
            "User-Agent: %s\r\n"\
            "Accept: %s\r\n"\
            "Require: www.onvif.org/ver20/backchannel\r\n"\
            "\r\n";
    const char format2[]=
            "DESCRIBE %s %s\r\n"\
            "CSeq: %d\r\n"\
            "User-Agent: %s\r\n"\
            "Accept: %s\r\n"\
            "Require: www.onvif.org/ver20/backchannel\r\n"\
            "Authorization: %s\r\n"\
            "\r\n";
    __TRY_AGAIN:
    sprintf(temp,"rtsp://%s:%d/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,m_pRtspInfo->streamName);
    if(m_pRtspInfo->bLogin==true){
        sprintf(m_pRtspInfo->payload,format1,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT,SDP_MEDIA_TYPE);
    }else{
        sprintf(url,"rtsp://%s:%d/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,m_pRtspInfo->streamName);
        if(HTTP_AUTH_setup(m_pRtspInfo->auth,m_pRtspInfo->userName,m_pRtspInfo->passWord,url,"DESCRIBE",szAuth,sizeof(szAuth))==AUTH_RET_FAIL){
            INFO_PRINT("talkbackRtspSetup_describe as talkbackRtspSetup_describe fail");
            return false;
        }
        sprintf(m_pRtspInfo->payload,format2,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT,SDP_MEDIA_TYPE,szAuth);
    }
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
    VLOG(VLOG_DEBUG,"request (size:%d) :\r\n %s \r\n",m_pRtspInfo->payloadSize,m_pRtspInfo->payload);
    if(sendRtspPacket()==false){
        INFO_PRINT("talkbackRtspSetup_describe as sendRtspPacket fail");
        return false;
    }
    if(readRtspMessage()==false){
        INFO_PRINT("talkbackRtspSetup_describe as readRtspMessage fail");
        return false;
    }
    if(parseRtspResponse(&nStatusCode,temp)==false){
        INFO_PRINT("talkbackRtspSetup_describe as parseRtspResponse fail");
        return false;
    }
    if((nStatusCode==rtspRStatusCodes[RTSP_RSC_UNAUTHORIZED].code)&&bAuthFlag==false){
        VLOG(VLOG_DEBUG,"require auth !!!");
        bAuthFlag=true;
        //此处可以设置回调函数从外界 获取 用户名和密码,暂时不实现
        goto __TRY_AGAIN;
    }else if(nStatusCode==rtspRStatusCodes[RTSP_RSC_UNAUTHORIZED].code){
        INFO_PRINT("talkbackRtspSetup_describe as auth failed !!!");
        //可以设置回调告知外界，用户验证失败
        return false;
    }
    return true;
}

bool TalkbackRtsp::talkbackRtspSetup_setup()
{
    int iSetupMedia=0;
    Attribute_t attr;
    int real_type=0;
    for(int i=0;i<m_pRtspInfo->sdp->media_num;i++){
        if(0==strcmp(m_pRtspInfo->sdp->media[i].media_n.type,"audio")){
            if(0==(m_pRtspInfo->stream_type&RTSP_STREAM_AUDIO)){
                VLOG(VLOG_DEBUG,"miss the audio as stream type do not support: %d",m_pRtspInfo->stream_type);
                continue;
            }
            if(m_pRtspInfo->sdp->media[i].media_n.format==0||
                    m_pRtspInfo->sdp->media[i].media_n.format==8){//pcma or pcmu
                if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[i].media_n.type,
                                      SDP_ATTR_SENDONLY,(void*)&attr,i)==RTSP_RET_FAIL){
                    continue;
                }
                if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[i].media_n.type,
                                      SDP_ATTR_CONTROL,(void*)&attr,i)==RTSP_RET_FAIL){
                    VLOG(VLOG_ERROR,"get media audio attr fail");
                    continue;
                }
                real_type=m_pRtspInfo->sdp->media[i].media_n.format;
                if(false==requestSeup(attr.value,m_pRtspInfo->sdp->media[i].media_n.type,
                                      m_pRtspInfo->sdp->media[i].media_n.format,real_type)){
                    VLOG(VLOG_ERROR,"setup audio fail");
                    goto CONNECT_ERR_EXIT;
                }
                iSetupMedia++;
                m_pRtspInfo->sdp->media[i].bRtspSetUp=1;
            }else if(m_pRtspInfo->sdp->media[i].media_n.format>=96
                     ||m_pRtspInfo->sdp->media[i].media_n.format==20
                     ||m_pRtspInfo->sdp->media[i].media_n.format==21
                     ||m_pRtspInfo->sdp->media[i].media_n.format==22
                     ||m_pRtspInfo->sdp->media[i].media_n.format==23){
                // 20 ~ 23 , unsigned payload type
                // >= 96: dynamic payload type , need to get detail media type by rtpmap attribute
                if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[i].media_n.type,
                                      SDP_ATTR_SENDONLY,(void*)&attr,i)==RTSP_RET_FAIL){
                    continue;
                }

                if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[i].media_n.type,
                                      SDP_ATTR_RTP_MAP,(void*)&attr,i)==RTSP_RET_OK){
                    if(strncmp(attr.rtpmap.codec_type,"PCMU",strlen("PCMU"))==0||
                       strncmp(attr.rtpmap.codec_type,"PCMA",strlen("PCMA"))==0){
                        if(strncmp(attr.rtpmap.codec_type,"PCMA",strlen("PCMA"))==0){
                            real_type=RTP_TYPE_PCMA;
                        }else{
                            real_type=RTP_TYPE_PCMU;
                        }
                        if(SDP_get_media_attr(m_pRtspInfo->sdp,m_pRtspInfo->sdp->media[i].media_n.type,
                                              SDP_ATTR_CONTROL,(void *)&attr,i)==RTSP_RET_FAIL){
                            INFO_PRINT("get media SDP_ATTR_CONTROL attr fail ,continue ,find next media");
                            continue;
                        }
                        if(requestSeup(attr.value,m_pRtspInfo->sdp->media[i].media_n.type,
                                       m_pRtspInfo->sdp->media[i].media_n.format,real_type)==RTSP_RET_FAIL){
                            INFO_PRINT("talkbackRtspSetup_setup fail as setup audio fail ");
                            goto CONNECT_ERR_EXIT;
                        }
                        m_pRtspInfo->sdp->media[i].bRtspSetUp=1;
                        iSetupMedia++;
                    }else{
                        VLOG(VLOG_DEBUG,"unknown audio codec type:%s",attr.rtpmap.codec_type);
                        continue;
                    }
                }else{
                    VLOG(VLOG_DEBUG,"get media SDP_ATTR_RTP_MAP attr fail");
                    continue;
                }
            }else{
                VLOG(VLOG_WARNING,"unknown audio type:%d",m_pRtspInfo->sdp->media[i].media_n.format);
            }
        }else if(0==strcmp(m_pRtspInfo->sdp->media[i].media_n.type,"video")){
            VLOG(VLOG_DEBUG,"ignore video media type");
            continue;
        }else{
            VLOG(VLOG_WARNING,"unknown media type: %s",m_pRtspInfo->sdp->media[i].media_n.type);
        }
    }
    if(iSetupMedia==0){
        goto CONNECT_ERR_EXIT;
    }
    return true;
CONNECT_ERR_EXIT:
    return false;
}

bool TalkbackRtsp::talkbackRtspPlay(char *control,int n)
{
    char temp[256];
    char stream_url[128];
    char *ptr = NULL;
    int nStatus_code;
    const char format[]=
        "PLAY %s %s\r\n"\
        "CSeq: %d\r\n"\
        "User-Agent: %s\r\n"\
        "Session: %s\r\n"\
        "Range: npt=0.000-\r\n"\
        "Require: www.onvif.org/ver20/backchannel\r\n"\
        "\r\n";
    strncpy(stream_url,m_pRtspInfo->streamName,sizeof(stream_url)-1);
    if ((ptr = strstr(stream_url, "?")) != NULL) {
        *ptr = '\0';
    }
    if(memcmp(control,"rtsp://",strlen("rtsp://"))==0){
        sprintf(temp,"%s",control);
    }else{
        sprintf(temp,"rtsp://%s:%d/%s/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,stream_url,control);
    }
    sprintf(m_pRtspInfo->payload,format,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT,m_pRtspInfo->session_id);
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
    VLOG(VLOG_DEBUG,"request (size : %d):\r\n%s\r\n",m_pRtspInfo->payloadSize,m_pRtspInfo->payload);
    if(sendRtspPacket()==false){
        return false;
    }
    if(readRtspMessage()==false){
        return false;
    }
    if(parseRtspResponse(&nStatus_code,temp)==false){
        if(nStatus_code==RTSP_RSC_UNSUPPORTED_TRANSPORT){
            VLOG(VLOG_ERROR,"server do not support udp transport,and client do not support tcp transport");
        }else{
            VLOG(VLOG_ERROR,"set up fail (nstatus_code:%d)",nStatus_code);
        }
        return false;
    }
    return true;
}
bool TalkbackRtsp::talkbackRtspKeepalive(char *control, int n)
{
    char temp[256];
    char tmp[256];
    char stream_url[128];
    char *ptr = NULL;
    int nStatus_code;
    char payload[RTSP_BUF_SIZE];
    int payload_size;
    const char format[]=
        "OPTIONS %s %s\r\n"\
        "CSeq: %d\r\n"\
        "User-Agent: %s\r\n"\
        "Require: www.onvif.org/ver20/backchannel\r\n"\
        "\r\n";

    const char format2[]=
        "GET_PARAMETER %s %s\r\n"\
        "CSeq: %d\r\n"\
        "User-Agent: %s\r\n"\
        "Session: %s\r\n"\
        "Require: www.onvif.org/ver20/backchannel\r\n"\
        "\r\n";
    strncpy(stream_url,m_pRtspInfo->streamName,sizeof(stream_url)-1);
    if ((ptr = strstr(stream_url, "?")) != NULL) {
        *ptr = '\0';
    }
    if(memcmp(control,"rtsp://",strlen("rtsp://"))==0){
        sprintf(temp,"%s",control);
    }else{
        sprintf(temp,"rtsp://%s:%d/%s/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,stream_url,control);
    }
    if(strstr(m_pRtspInfo->allow_method,"GET_PARAMETER")!=NULL){
        sprintf(m_pRtspInfo->payload,format2,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT,m_pRtspInfo->session_id);
        m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
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
    }
    sprintf(m_pRtspInfo->payload,format,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT);
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
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
void TalkbackRtsp::talkbackRtspTeardown(char *control, int n)
{
    char temp[256];
    char stream_url[128];
    char *ptr = NULL;
    int nStatus_code;
    const char format[]=
        "TEARDOWN %s %s\r\n"\
        "CSeq: %d\r\n"\
        "User-Agent: %s\r\n"\
        "Session: %s\r\n"\
        "Require: www.onvif.org/ver20/backchannel\r\n"\
        "\r\n";
    strncpy(stream_url,m_pRtspInfo->streamName,sizeof(stream_url)-1);
    if ((ptr = strstr(stream_url, "?")) != NULL) {
        *ptr = '\0';
    }
    if(memcmp(control,"rtsp://",strlen("rtsp://"))==0){
        sprintf(temp,"%s",control);
    }else{
        sprintf(temp,"rtsp://%s:%d/%s/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,stream_url,control);
    }
    sprintf(m_pRtspInfo->payload,format,temp,RTSP_VERSION,++m_pRtspInfo->cseq,RTSP_USER_AGENT,m_pRtspInfo->session_id);
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
    VLOG(VLOG_DEBUG,"request (size : %d):\r\n%s\r\n",m_pRtspInfo->payloadSize,m_pRtspInfo->payload);

    sendRtspPacket();
}



bool TalkbackRtsp::requestSeup(char *control, char *media_type, int type, int real_type)
{
    char temp[256];
    char temp2[256];
    char stream_url[128];
    char *ptr = NULL;
    int nStatus_code;
    TalkbackRtcp **pTalkbackRtcp=NULL;
    TalkbackRtp **pTalkbackRtp=NULL;
    unsigned int chn_port_tmp = 0;
    SOCK_t rtp_sock;
    int rtp_chn_port=0,rtcp_chn_port = 0;
    const char format[]=
            "SETUP %s %s\r\n"\
            "CSeq: %d\r\n"\
            "User-Agent: %s\r\n"\
            "Transport: %s\r\n"\
            "Require: www.onvif.org/ver20/backchannel\r\n"\
            "\r\n";
    const char format2[]=
            "SETUP %s %s\r\n"\
            "CSeq: %d\r\n"\
            "User-Agent: %s\r\n"\
            "Transport: %s\r\n"\
            "Session: %s\r\n"\
            "Require: www.onvif.org/ver20/backchannel\r\n"\
            "\r\n";
    if(m_pRtspInfo->transport==RTP_AUTO){
#if RTSP_RTP_DEF_TRANSPORT==RTSP_RTP_OVER_RTSP
        m_pRtspInfo->b_interleavedMode=RTSP_RTP_OVER_RTSP;
        m_pRtspInfo->low_transport=RTP_TRANSPORT_TCP;
#else
        m_pRtspInfo->b_interleavedMode=RTSP_RTP_OVER_UDP;
        m_pRtspInfo->low_transport=RTP_TRANSPORT_UDP;
#endif
    }else if(m_pRtspInfo->transport==RTP_UDP){
        m_pRtspInfo->low_transport=RTP_TRANSPORT_UDP;
        m_pRtspInfo->b_interleavedMode=RTSP_RTP_OVER_UDP;
    }else{
        m_pRtspInfo->low_transport=RTP_TRANSPORT_TCP;
        m_pRtspInfo->b_interleavedMode=RTSP_RTP_OVER_RTSP;
    }
    strncpy(stream_url,m_pRtspInfo->streamName,sizeof(stream_url)-1);
    if ((ptr = strstr(stream_url, "?")) != NULL) {
        *ptr = '\0';
    }
TRY_INTERLEAVED_MODE:
    if(memcmp(control,"rtsp://",strlen("rtsp://"))==0){
        sprintf(temp,"%s",control);
    }else{
        sprintf(temp,"rtsp://%s:%d/%s/%s",m_pRtspInfo->ip,m_pRtspInfo->nPort,stream_url,control);
    }
    if(m_pRtspInfo->b_interleavedMode==true){
        if(0==strcmp(media_type,"audio")){
            m_pRtspInfo->channel=2;
        }else{
            m_pRtspInfo->channel=0;
        }
        m_pRtspInfo->client_port=m_pRtspInfo->channel;
        m_pRtspInfo->server_port=m_pRtspInfo->channel;
    }else{
        if(getSocketGroup(m_pRtspInfo->pSocketGroup)==false){
            INFO_PRINT("requestSeup fail as getSocketGroup fail");
            return false;
        }
        m_pRtspInfo->client_port=m_pRtspInfo->pSocketGroup->rtp_port;
    }
    rtsp_setup_transport(temp2);
    if(m_pRtspInfo->session_id[0]==0){
        sprintf(m_pRtspInfo->payload,format,temp,RTSP_VERSION,
                ++m_pRtspInfo->cseq,
                RTSP_USER_AGENT,
                temp2);
    }else{
        sprintf(m_pRtspInfo->payload,format2,temp,RTSP_VERSION,
                ++m_pRtspInfo->cseq,
                RTSP_USER_AGENT,
                temp2,
                m_pRtspInfo->session_id);
    }
    m_pRtspInfo->payloadSize=strlen(m_pRtspInfo->payload);
    VLOG(VLOG_DEBUG,"request (size :%d):\r\n%s\r\n",m_pRtspInfo->payloadSize,m_pRtspInfo->payload);
    if(sendRtspPacket()==false){
        return false;
    }
    if(readRtspMessage()==false){
        return false;
    }
    if(parseRtspResponse(&nStatus_code,temp)==false){
        if(nStatus_code==RTSP_RSC_UNSUPPORTED_TRANSPORT){
            VLOG(VLOG_ERROR,"server do not support udp transport,and client do not support tcp transport");
        }else{
            VLOG(VLOG_ERROR,"set up fail (nstatus_code:%d)",nStatus_code);
        }
        return false;
    }
    if(0==strcmp(media_type,"audio")){
        pTalkbackRtp=(TalkbackRtp **)(&m_pRtspInfo->pRtp_audio);
#ifdef TALKBACK_RTCP_ENABLE
        pTalkbackRtcp=(TalkbackRtcp **)(&m_pRtspInfo->pRtcp_audio);
        m_pRtspInfo->pRtcp_audio=new TalkbackRtcp;
#endif
        m_pRtspInfo->pRtp_audio=new TalkbackRtp;
    }else if(0==strcmp(media_type,"video")){
#ifdef TALKBACK_RTCP_ENABLE
        m_pRtspInfo->pRtcp_video=new TalkbackRtcp;
        pTalkbackRtcp=(TalkbackRtcp **)(&m_pRtspInfo->pRtcp_video);
#endif
        pTalkbackRtp=(TalkbackRtp **)(&m_pRtspInfo->pRtp_video);
        m_pRtspInfo->pRtp_video=new TalkbackRtp;
    }else{
        VLOG(VLOG_ERROR,"setup:unsuport payload type:%s  -%d",media_type,type);
        return false;
    }
    VLOG(VLOG_DEBUG,"%s setup :c_port:%d,s_port:%d",control,m_pRtspInfo->client_port,m_pRtspInfo->server_port);
    if(m_pRtspInfo->b_interleavedMode){
        if((m_pRtspInfo->channel%2)==0){
            rtp_chn_port=m_pRtspInfo->channel;
            rtcp_chn_port=m_pRtspInfo->channel+1;
        }else{
            rtp_chn_port=m_pRtspInfo->channel+1;
            rtcp_chn_port=m_pRtspInfo->channel;
        }
        rtp_sock=m_pRtspInfo->rtspSocket;
    }else{
        if((m_pRtspInfo->server_port%2)==0){
            rtp_chn_port=m_pRtspInfo->server_port;
            rtcp_chn_port=m_pRtspInfo->server_port+1;
        }else{
            rtp_chn_port=m_pRtspInfo->server_port+1;
            rtcp_chn_port=m_pRtspInfo->server_port;
        }
        rtp_sock=m_pRtspInfo->pSocketGroup->rtp_socket;
        if(-1==rtp_sock){
            VLOG(VLOG_ERROR,"setup request fail as SOCK_udp_init fail:(port:%d)",m_pRtspInfo->client_port);
            return false;
        }
    }
    (*pTalkbackRtp)->init(rtp_sock,rtp_chn_port,m_pRtspInfo->client_port,m_pRtspInfo->low_transport,real_type,m_pRtspInfo->ip);
#ifdef TALKBACK_RTCP_ENABLE
    (*pTalkbackRtcp)->init(rtcp_chn_port,m_pRtspInfo->pSocketGroup->rtcp_port,m_pRtspInfo->low_transport,m_pRtspInfo->role,m_pRtspInfo->cast_type,m_pRtspInfo->b_interleavedMode,m_pRtspInfo->rtspSocket,m_pRtspInfo->pSocketGroup->rtcp_socket,*pTalkbackRtp);
#endif

    return true;
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
    memset(m_pRtspInfo->payload,0,sizeof(m_pRtspInfo->payload));
    do{
        if(nReadedSize+nExpectSize>RTSP_BUF_SIZE){
            VLOG(VLOG_ERROR,"expect rtsp buffer size out of range,readed:%d expected:%d",nReadedSize,nExpectSize);
            return false;
        }
        nRevice=recv(m_pRtspInfo->rtspSocket,pEndPoint,nExpectSize,0);
        if(nRevice<0){
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
        VLOG(VLOG_ERROR,"invaild response format, not found cseq;palyload:%s",m_pRtspInfo->payload);
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
    if(http_get_string(m_pRtspInfo->payload,"Transport:",temp)==true){
        parseRtspTransport(temp);
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

bool TalkbackRtsp::parseRtspTransport(char *buf)
{
    char transport[128];
    *buf=0;
    char *pTransport=transport;
    char *pTemp;
    if(http_get_string(m_pRtspInfo->payload,"Transport:",transport)==false){
        return false;
    }

    if((pTemp=strstr(pTransport,"RTP/AVP/TCP"))!=NULL){
        m_pRtspInfo->low_transport=RTP_TRANSPORT_TCP;
        strcat(buf,"RTP/AVP/TCP");
    }else{
        strcat(buf,"RTP/AVP/UDP");
        m_pRtspInfo->low_transport=RTP_TRANSPORT_UDP;
    }

    if((pTemp=strstr(pTransport,"multicast"))!=NULL){
        m_pRtspInfo->cast_type=RTP_MULTICAST;
        strcat(buf,";multicast");
    }else{
        m_pRtspInfo->cast_type=RTP_UNICAST;
        strcat(buf,";unicast");
    }

    if((pTemp=strstr(pTransport,"interleaved"))!=NULL){
        m_pRtspInfo->b_interleavedMode=true;
        pTemp+=strlen("interleaved=");
        sscanf(pTemp,"%d%*s",&m_pRtspInfo->channel);
        pTemp=buf+strlen(buf);
        sprintf(pTemp,";interleaved=%d-%d",m_pRtspInfo->channel,m_pRtspInfo->channel+1);
        m_pRtspInfo->client_port=m_pRtspInfo->channel;
        m_pRtspInfo->server_port=m_pRtspInfo->channel;
    }else{
        m_pRtspInfo->b_interleavedMode=false;
        if((pTemp=strstr(pTransport,"client_port"))!=NULL){
            pTemp+=strlen("client_port=");
            printf("pTemp:%s \n",pTemp);
            sscanf(pTemp,"%d%*s",&m_pRtspInfo->client_port);
        }
        if((pTemp=strstr(pTransport,"server_port"))!=NULL){
            pTemp+=strlen("server_port=");
            sscanf(pTemp,"%d%*s",&m_pRtspInfo->server_port);
        }
        pTemp=buf+strlen(buf);
        sprintf(pTemp,";client_port=%d-%d;server_port=%d-%d",
                m_pRtspInfo->client_port,m_pRtspInfo->client_port+1,m_pRtspInfo->server_port,m_pRtspInfo->server_port+1);
    }
    if(m_pRtspInfo->role==RTSP_SERVER){
        pTemp=buf+strlen(buf);
        sprintf(pTemp,";ssrc=%x",m_pRtspInfo->streamName);
    }else{
        if((pTemp=strstr(pTransport,"ssrc="))!=NULL){
            pTemp+=strlen("ssrc=");
            sscanf(pTemp,"%x%*s",&m_pRtspInfo->ssrc);
        }else{
            m_pRtspInfo->ssrc=0;
        }
    }
    if((pTemp=strstr(pTransport,"mode"))!=NULL){
        pTemp+=strlen("mode=\"");
        if(strcmp(pTemp,"PLAY")==0){
            m_pRtspInfo->work_mode=RTSP_MODE_PLAY;
            strcat(buf,";mode=\"PLAY\"");
        }else if(strcmp(pTemp,"RECODE")){
            m_pRtspInfo->work_mode=RTSP_MODE_RECORD;
            strcat(buf,";mode=\"RECORD\"");
        }
    }
    VLOG(VLOG_DEBUG,"parse transport:client_port:%d server_port:%d,%s",
    m_pRtspInfo->client_port,m_pRtspInfo->server_port,m_pRtspInfo->cast_type ? "multicast" : "unicast");
    VLOG(VLOG_DEBUG,"Transport: %s",buf);
    return true;
}

bool TalkbackRtsp::rtsp_setup_transport(char *buf)
{
    char *pTemp=buf;
    if(m_pRtspInfo->low_transport==RTP_TRANSPORT_TCP){
        sprintf(pTemp,"RTP/AVP/TCP");
    }else{
        sprintf(pTemp,"RTP/AVP");
    }
    pTemp=buf+strlen(buf);
    if(m_pRtspInfo->cast_type==RTP_MULTICAST){
        sprintf(pTemp,";multicast");
    }else{
        sprintf(pTemp,";unicast");
    }
    pTemp=buf+strlen(buf);
    if(m_pRtspInfo->b_interleavedMode==true){
        sprintf(pTemp,";interleaved=%d-%d",m_pRtspInfo->channel,m_pRtspInfo->channel+1);
    }else{
        sprintf(pTemp,";client_port=%d-%d",m_pRtspInfo->client_port,m_pRtspInfo->client_port+1);
    }
    return true;
}

uint32_t TalkbackRtsp::hash_string(char *str)
{
#define HASHWORDBITS	(32)
    uint32_t hval=0xFFFFFFFF,g;
    char *pstr=str;
    while(*str){
        hval <<=4;
        hval += (unsigned char)*str++;
        g = hval & ((unsigned int)0xf << (HASHWORDBITS -4));
        if(g != 0){
            hval ^= g >> (HASHWORDBITS - 8);
            hval ^= g;
        }
    }

    VLOG(VLOG_DEBUG,"string:%s hashval:%x",pstr,hval);
    return hval;
}



bool TalkbackRtsp::getSocketGroup(RTSP_SOCKET_GROUP *rsg)
{
    if(NULL==rsg){
        return false;
    }
    int rtpSocket=-1;
    unsigned short rtpPort=0;
    int rtcpSocket=-1;
    bool ret=false;
    while(1){
        rtpSocket=getAvailablePort(rtpPort);
        if(rtpSocket==-1){
            continue;
        }
        if((rtpPort&1)){
            SOCK_close(rtpSocket);
            continue;
        }
        rtcpSocket=createSocket(rtpPort+1);
        if(rtcpSocket==-1){
            SOCK_close(rtpSocket);
            continue;
        }
        ret =true;
        break;
    }
    if(ret==true){
        rsg->rtcp_port=rtpPort+1;
        rsg->rtcp_socket=rtcpSocket;
        rsg->rtp_port=rtpPort;
        rsg->rtp_socket=rtpSocket;
    }
    return ret;
}

int TalkbackRtsp::getAvailablePort(unsigned short &port)
{
//lock;
    return SOCK_udp_init_2(NULL,&port,RTSP_SOCK_TIMEOUT);
}

int TalkbackRtsp::createSocket(int port)
{
    return SOCK_udp_init(NULL,port,RTSP_SOCK_TIMEOUT);
}












