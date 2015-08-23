#ifndef AUDIODATA_H
#define AUDIODATA_H
#include"TalkBackDataTypeCommon.h"
#if defined(__cplusplus)
extern "C" {
#endif

TalkbackAudioCapture_API  bool TALKBACKCALL checkClientIsSupportTalkback();
TalkbackAudioCapture_API bool TALKBACKCALL checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode);
TalkbackAudioCapture_API int  TALKBACKCALL getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode);
TalkbackAudioCapture_API bool TALKBACKCALL applyAudio(tagAudioContext *pContext,tagAudioCodeMode tCodeMode,AudioErrorCallback pErrorCallback);
TalkbackAudioCapture_API bool TALKBACKCALL releaseAudio(tagAudioContext *pContext);
TalkbackAudioCapture_API bool TALKBACKCALL getData(tagAudioContext *pContext, char *pBuff,int pBuffSize,int &nSize,talkback_int64 &nTimeStamp);

#if defined(__cplusplus)
}
#endif

#endif // AUDIODATA_H
