#ifndef TALKBACKRTP_H
#define TALKBACKRTP_H


typedef struct __tagTalkbackRtpInfo{

}tagTalkbackRtpInfo;
class TalkbackRtp
{
public:
    TalkbackRtp();
    ~TalkbackRtp();
    bool init(tagTalkbackRtpInfo* pRtpInfo);
    bool sendbuf();
    void deinit();
private:
    tagTalkbackRtpInfo *m_pRtpInfo;
};

#endif // TALKBACKRTP_H
