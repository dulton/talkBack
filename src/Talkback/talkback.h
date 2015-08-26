#ifndef TALKBACK_H
#define TALKBACK_H

#include "talkback_global.h"
#include "TalkBackDataTypeCommon.h"
class TALKBACKSHARED_EXPORT Talkback
{

public:
    explicit Talkback();
    ~Talkback();
    bool startTalkback(lpTalkbackContext parm);
    bool pauseTalkback(lpTalkbackContext parm);

    static bool checkClientIsSupportTalkback();

    bool addDeviceToTalkback(lpTalkbackContext parm,tagTalkBackMode tMode);
    bool removeDeviceFromTalkback(lpTalkbackContext parm);
private:
    lpTalkbackContext m_pContext;
};

#endif // TALKBACK_H
