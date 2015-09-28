#ifndef TALKBACKCINTERFACE_H
#define TALKBACKCINTERFACE_H


#include "TalkbackInterfaceCommon.h"
#if defined(__cplusplus)
extern "C"{
#endif

TalkbackInterface_API bool TALKBACKCALL startTalkback(void *thiz);
TalkbackInterface_API bool TALKBACKCALL pauseTalkback(void *thiz);

TalkbackInterface_API bool TALKBACKCALL checkClientIsSupportTalkback();
TalkbackInterface_API void* TALKBACKCALL initTalkback();
TalkbackInterface_API bool  TALKBACKCALL deinitTalkback(void *thiz);
TalkbackInterface_API bool TALKBACKCALL addDeviceToTalkback(void *thiz,int tMode,void *userContent,char*userName,char *password,char *url,char *ip,int nPort,void* errorEventHook);
TalkbackInterface_API bool TALKBACKCALL removeDeviceFromTalkback(void *thiz);

#if defined(__cplusplus)
}
#endif// __cplusplus





#endif // TALKBACKCINTERFACE_H
