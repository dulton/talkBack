#ifndef TALKBACKMANAGER_H
#define TALKBACKMANAGER_H

#include "TalkBackDataTypeCommon.h"
#include "talkbacklock.h"

struct __tagTalkbackNode;
class TalkbackManager
{
public:
    TalkbackManager();
    ~TalkbackManager();
    void initManager();
    void deinitManager();

    bool startTalkback(lpTalkbackContext parm);
    bool pauseTalkback(lpTalkbackContext parm);

    static bool checkClientIsSupportTalkback();

    bool addDeviceToTalkback(lpTalkbackContext parm,tagTalkBackMode tMode);
    bool removeDeviceFromTalkback(lpTalkbackContext parm);
private:
    void clearTalkbackNodeList();
private:
    __tagTalkbackNode *m_pTalkbackNodeList;
    TalkbackLock m_tTalkbackNodeListLock;
};

#endif // TALKBACKMANAGER_H
