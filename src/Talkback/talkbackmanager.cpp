#include "talkbackmanager.h"
#include "talkbackcore.h"
typedef struct __tagTalkbackNode{
    lpTalkbackContext pTalkbackContext;
    TalkbackCore *pTalkbackCore;
    __tagTalkbackNode *pNext;
}tagTalkbackNode;
TalkbackManager::TalkbackManager():m_pTalkbackNodeList(NULL)
{
}

TalkbackManager::~TalkbackManager()
{

}

void TalkbackManager::initManager()
{

}

void TalkbackManager::deinitManager()
{
    clearTalkbackNodeList();
}

bool TalkbackManager::startTalkback(lpTalkbackContext parm)
{

}

bool TalkbackManager::pauseTalkback(lpTalkbackContext parm)
{

}

bool TalkbackManager::checkClientIsSupportTalkback()
{
    return TalkbackCore::checkClientIsSupportTalkback();
}

bool TalkbackManager::addDeviceToTalkback(lpTalkbackContext parm, tagTalkBackMode tMode)
{
    m_tTalkbackNodeListLock.lock();
    m_tTalkbackNodeListLock.unlock();
}

bool TalkbackManager::removeDeviceFromTalkback(lpTalkbackContext parm)
{

}

void TalkbackManager::clearTalkbackNodeList()
{

}
