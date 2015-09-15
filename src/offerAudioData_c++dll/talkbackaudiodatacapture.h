#ifndef TALKBACKAUDIODATACAPTURE_H
#define TALKBACKAUDIODATACAPTURE_H
#include "TalkBackDataTypeCommon.h"
#include "talkbacklock.h"
#include "talkbackthread.h"


typedef struct __tagCaptureDataInfo{
    char *pCaptureData;
    int nDataSize;
    talkback_int64 nTimeStamp;
}tagCaptureDataInfo,*pCaptureDataInfo;
typedef enum __tagAudioDataCaptureError{
    DataCapture_Thread_Unwork,
    DataCapture_Microphone_Undetect,
    DataCapture_Unknow_Error,
    DataCapture_Error_Size,
}tagAudioDataCaptureError;
typedef struct __tagCapureContexInfo{
    tagCaptureDataInfo tDataList[AUDIODATALISTSIZE];
    tagAudioCodeMode tCodeMode;
    talkback_int64 nCurrentTimeStamp;
    TalkbackLock *pDataLock;
}tagCapureContexInfo;

typedef void (*AudioDataCaptureErrorCallback)(void *parm,tagAudioDataCaptureError tError,char *pErrorInfo);
typedef struct __tagAudioCaptureCallbackStruct{
    void * parm;
    AudioDataCaptureErrorCallback pCallBack;
    __tagAudioCaptureCallbackStruct *pNext;
}tagAudioCaptureCallbackStruct;
class TalkbackAudioDataCapture
{
public:
    explicit TalkbackAudioDataCapture();
    ~TalkbackAudioDataCapture();
    static bool checkClientIsSupportTalkback();

    void initCapture();
    void deinitCapture();

    void addCodeToCapture(tagCapureContexInfo *pContexInfo);
    void removeCodeFromCapture(tagCapureContexInfo *pContexInfo);

    void setCaptureErrorCallbackFunc(void *parm, AudioDataCaptureErrorCallback Func);
    void removeCaptureErrorCallbackFunc(void *parm);

    static int getFrameSize();

    TALKBACK_THREAD_RET_TYPE startCodeThread(void *arg);
private:
    bool reCheckClientIsSupportTalkback();

    void errorCallBack(tagAudioDataCaptureError tError,char *ErrorInfo);
    void audioDataCaptureStep_dispatachData(char *pBuff);
    void copyBuffToContexList(int n,talkback_int64 nMax,char *pBuff);
private:
    tagCapureContexInfo *m_pContexList[AUDIO_CODE_MODE_SIZE];
    TalkbackLock m_tContextListLock;
    TalkbackLock m_tCaptureCallbackListLock;

    TALKBACK_THREAD_HANDLE m_tThreadId;
    volatile bool m_bThreadStop;
    bool m_bClientIsSupportTalkback;
    tagAudioCaptureCallbackStruct *m_pCaptureCallbackList;
};

#endif // TALKBACKAUDIODATACAPTURE_H
