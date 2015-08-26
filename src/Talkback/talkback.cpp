#include "talkback.h"
#include "talkbackmanager.h"
#include "talkbacklock.h"

static TalkbackLock g_csTalkbackManagerLock;
static int g_nTalkbackManagerCount=0;
static TalkbackManager *g_pTalkbackManager=NULL;
void applyTalkbackManager(){
    g_csTalkbackManagerLock.lock();
    if(0==g_nTalkbackManagerCount){
        g_pTalkbackManager=new TalkbackManager;
        g_pTalkbackManager->initManager();
    }else{

    }
    g_nTalkbackManagerCount++;
    g_csTalkbackManagerLock.unlock();
}
void releaseTalkbackManger(){
    g_csTalkbackManagerLock.lock();
    if(g_nTalkbackManagerCount>0){
        g_nTalkbackManagerCount--;
        if(0==g_nTalkbackManagerCount){
            g_pTalkbackManager->deinitManager();
            delete g_pTalkbackManager;
            g_pTalkbackManager=NULL;
        }
    }else{
        //do nothing
    }
    g_csTalkbackManagerLock.unlock();
}

Talkback::Talkback():m_pContext(NULL)
{
    applyTalkbackManager();
}

Talkback::~Talkback()
{
    if(NULL!=m_pContext){
        g_pTalkbackManager->removeDeviceFromTalkback(m_pContext);
    }
    releaseTalkbackManger();
}

bool Talkback::startTalkback(lpTalkbackContext parm)
{
    return g_pTalkbackManager->startTalkback(parm);
}

bool Talkback::pauseTalkback(lpTalkbackContext parm)
{
    return g_pTalkbackManager->pauseTalkback(parm);
}

bool Talkback::checkClientIsSupportTalkback()
{
    return TalkbackManager::checkClientIsSupportTalkback();
}

bool Talkback::addDeviceToTalkback(lpTalkbackContext parm, tagTalkBackMode tMode)
{
    if(g_pTalkbackManager->addDeviceToTalkback(parm,tMode)){
        m_pContext=parm;
        return true;
    }else{
        return false;
    }
}

bool Talkback::removeDeviceFromTalkback(lpTalkbackContext parm)
{
    m_pContext=NULL;
    return g_pTalkbackManager->removeDeviceFromTalkback(parm);
}
