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

bool TalkbackRtsp::readRtspMessage()
{

}

bool TalkbackRtsp::parseRtspResponse(int *statusCode, char *info)
{

}



