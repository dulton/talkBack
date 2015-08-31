#include "talkbackrtp.h"
#include "TalkBackDataTypeCommon.h"

TalkbackRtp::TalkbackRtp():m_pRtpInfo(NULL)
{
}

TalkbackRtp::~TalkbackRtp()
{

}

bool TalkbackRtp::init(tagTalkbackRtpInfo* pRtpInfo)
{
    m_pRtpInfo=pRtpInfo;
}

bool TalkbackRtp::sendbuf()
{

}

void TalkbackRtp::deinit()
{

}
