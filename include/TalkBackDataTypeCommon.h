#ifndef TALKBACKCOMMON_H
#define TALKBACKCOMMON_H


#if defined(_WIN32)
 #define TALKBACKCALL __cdecl
#else
 #define TALKBACKCALL
#endif

typedef  enum __tagAudioCodeMode{
    AUDIO_CODE_G711_A=0,
    AUDIO_CODE_C711_U,
    AUDIO_CODE_MODE_SIZE,
}tagAudioCodeMode;
typedef enum __tagTalkbackAudioError{
    AUDIO_MICROPHONE_UNDETECT,
    AUDIO_CODE_TYPE_UNSUPPORT,
    AUDIO_UNKNOW_ERROR,
    AUDIO_ERROR_SIZE,
}tagTalkbackAudioError;
typedef void (TALKBACKCALL *AudioErrorCallback)(void *parm,tagTalkbackAudioError tError,char *pErrorInfo);


typedef struct __tagAudioContext{
    void *pUserContext;
    void *pAudioDataContext;
}tagAudioContext ,*ptagAudioContext;

#ifndef talkback_int64
#define talkback_int64 long long
#endif //int64

#define AUDIODATALISTSIZE 50

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef TalkbackAudioCapture_API
 #if defined(_WIN32)
  #define TalkbackAudioCapture_API __declspec(dllimport)
 #else
  #define TalkbackAudioCapture_API extern
 #endif
#endif

#if defined(__cplusplus)
}
#endif

#endif // TALKBACKCOMMON_H
