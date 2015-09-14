#ifndef AUDIOCODE_H
#define AUDIOCODE_H
#include "TalkBackDataTypeCommon.h"
#include "talkbackthread.h"

class TalkbackLock;

#define SupportG711_Alaw true;
#define SupportG711_Ulaw true;
#define G711_Alaw_Size 320
#define G711_Ulaw_Size 320
namespace AudioCodeSpace {
typedef struct __tagAudioDataNode{
    char *pData;
    talkback_int64 tTimeStamp;
    int nSize;
}tagAudioDataNode;
typedef struct __tagApplyAudioNode{
    void *parm;
    AudioErrorCallback pErrorCallback;
    tagAudioCodeMode tCodeMode;
    tagAudioDataNode tDataNodeList[AUDIODATALISTSIZE];
    talkback_int64 nMaxTimeStamp;
    __tagApplyAudioNode *pNext;
}tagApplyAudioNode;
}

class AudioCode
{
public:
    explicit AudioCode();
    ~AudioCode();
    static bool checkClientIsSupportTalkback();
    static bool checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode);
    static int  getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode);

    bool getData(void *parm,char *pBuff,int pBufferSize,int &nSize,talkback_int64 &nTimeStamp);
    bool applyAudio(void *parm,tagAudioCodeMode tCodeMode,AudioErrorCallback pErrorCallback);
    bool releaseAudio(void *parm);
    void initAudio();
    void deinitAudio();

    TALKBACK_THREAD_RET_TYPE startCodeThread(void *arg);
    void errorCallBack(tagTalkbackAudioError tError,char *pErrorInfo);
private:
    void disPatchBuff(char *pBuff,tagAudioCodeMode tCodeMode,talkback_int64 nTimeStamp);
    bool releaseAudioEx(void *parm);
private :
    static bool m_bIsSupportG711_Alaw;
    static bool m_bIsSupportG711_Ulaw;
    static int m_nG711_Alaw_Size;
    static int m_nG711_Ulaw_Size;

private:
    TALKBACK_THREAD_HANDLE m_tCodeThreadId;
    bool m_bCodeThreadStop;
    TalkbackLock *m_pApplyAudioNodeListLock;
    AudioCodeSpace::tagApplyAudioNode *m_pApplyAudioNodeList;
    bool m_bNeedEncodeG711_Alaw;
    bool m_bNeedEncodeG711_Ulaw;
    int m_nNeedEncodeCountG711_Alaw;
    int m_nNeedEncodeCountG711_Ulaw;
};

#endif // AUDIOCODE_H
