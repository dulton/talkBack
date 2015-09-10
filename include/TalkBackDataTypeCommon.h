#ifndef TALKBACKCOMMON_H
#define TALKBACKCOMMON_H


#if defined(_WIN32)
 #define TALKBACKCALL __cdecl
#else
 #define TALKBACKCALL
#endif

#ifndef NULL
#define NULL 0
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
typedef enum __tagTalkbackCInterfaceError{
    tagTalkbackCInterface_microphone_undetect,//麦克风设备不在线
    tagTalkbackCInterface_parm_error,//输入参数错误
    tagTalkbackCInterface_device_outOfLine,//对方设备不在线
    tagTalkbackCInterface_device_unsupport,//对方设备不支持语音回传功能
    tagTalkbackCInterface_num_outOfRange,//超出语音最大连接数
    tagTalkbackCInterface_codeMode_unsupport,//不支持该编码格式
    tagTalkbackCInterface_unknow_error,//未知错误
    tagTalkbackCInterface_error_size,//
}tagTalkbackCInterfaceError;
typedef enum __tagTalkBackMode{
    TALKBACK_EXCLUSIVE,//对讲独占模式，用于一对一对讲
    TALKBACK_SHARE,//对讲共享模式，用于广播
    TALKBACK_MODE_SIZE,
}tagTalkBackMode;
typedef void (TALKBACKCALL *AudioErrorCallback)(void *parm,tagTalkbackAudioError tError,char *pErrorInfo);
typedef void (TALKBACKCALL *TalkbackInterfaceErrorCallback)(void *parm ,tagTalkbackCInterfaceError tError,char *pErrorInfo);

typedef struct __tagAudioContext{
    void *pUserContext;
    void *pAudioDataContext;
}tagAudioContext ,*ptagAudioContext;

typedef struct __tagTalkbackContext{
    void    *pUserContext;
    void    *pTalkbackContext;
    char    userName[256];
    char    passWord[256];
    int     nPort;
    char    url[256];
    char    ip[20];
    TalkbackInterfaceErrorCallback errorEventHook;
}tagTalkbackContext,*lpTalkbackContext;

#ifndef talkback_int64
#define talkback_int64 long long
#endif //int64

#define AUDIODATALISTSIZE 50

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef TalkbackInterface_API
 #if defined(_WIN32)
  #define TalkbackInterface_API __declspec(dllimport)
 #else
  #define TalkbackInterface_API extern
 #endif
#endif


#if defined(__cplusplus)
}
#endif

#endif // TALKBACKCOMMON_H
