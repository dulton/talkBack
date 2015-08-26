#ifndef TALKBACKCINTERFACE_H
#define TALKBACKCINTERFACE_H

#include "TalkBackDataTypeCommon.h"

#if defined(__cplusplus)
extern "C"{
#endif

TalkbackInterface_API bool TALKBACKCALL startTalkback(lpTalkbackContext parm);
TalkbackInterface_API bool TALKBACKCALL pauseTalkback(lpTalkbackContext parm);

TalkbackInterface_API bool TALKBACKCALL checkClientIsSupportTalkback();

TalkbackInterface_API bool TALKBACKCALL addDeviceToTalkback(lpTalkbackContext parm,tagTalkBackMode tMode);
TalkbackInterface_API bool TALKBACKCALL removeDeviceFromTalkback(lpTalkbackContext parm);

#if defined(__cplusplus)
}
#endif// __cplusplus





#endif // TALKBACKCINTERFACE_H
