#include "talkbackmanager.h"
#include "talkbackcore.h"
#include "TalkBackCommonTool.h"
typedef struct TalkbackNode{
    lpTalkbackContext pTalkbackContext;
    TalkbackCore *pTalkbackCore;
    TalkbackNode *pNext;
}tagTalkbackNode;
TalkbackManager::TalkbackManager():m_pTalkbackNodeList(NULL)
{

}

TalkbackManager::~TalkbackManager()
{

}

void TalkbackManager::initManager()
{
    return;
}

void TalkbackManager::deinitManager()
{
    clearTalkbackNodeList();
}

bool TalkbackManager::startTalkback(lpTalkbackContext parm)
{
    bool bRet=false;
    m_tTalkbackNodeListLock.lock();
    tagTalkbackNode *pFind=m_pTalkbackNodeList;
    while(NULL!=pFind){
        if(pFind->pTalkbackContext==parm){
           bRet= pFind->pTalkbackCore->startTalkback();
            break;
        }
        pFind=pFind->pNext;
    }
    m_tTalkbackNodeListLock.unlock();
    return bRet;
}

bool TalkbackManager::pauseTalkback(lpTalkbackContext parm)
{
    bool bRet=false;
    m_tTalkbackNodeListLock.lock();
    tagTalkbackNode *pFind=m_pTalkbackNodeList;
    while(NULL!=pFind){
        if(pFind->pTalkbackContext==parm){
           bRet= pFind->pTalkbackCore->pauseTalkback();
            break;
        }
        pFind=pFind->pNext;
    }
    m_tTalkbackNodeListLock.unlock();
    return bRet;
}

bool TalkbackManager::checkClientIsSupportTalkback()
{
    return TalkbackCore::checkClientIsSupportTalkback();
}

bool TalkbackManager::addDeviceToTalkback(lpTalkbackContext parm, tagTalkBackMode tMode)
{
    m_tTalkbackNodeListLock.lock();
    if(NULL==parm){
        INFO_PRINT("addDeviceToTalkback fail as parm is null");
        m_tTalkbackNodeListLock.unlock();
        return false;
    }
    if(TalkbackCore::checkClientIsSupportTalkback()==false){
        m_tTalkbackNodeListLock.unlock();
        INFO_PRINT("addDeviceToTalkback fail as client do not supporttalkback");
        return false;
    }
    tagTalkbackNode *pTalkbackNodeNext=new tagTalkbackNode;
    pTalkbackNodeNext->pNext=NULL;
    pTalkbackNodeNext->pTalkbackContext=parm;
    TalkbackCore *pTalkbackCore=new TalkbackCore;
    pTalkbackNodeNext->pTalkbackCore=pTalkbackCore;
    if(pTalkbackCore->initTalkback(parm)==false){
        pTalkbackCore->deinitTalkback();
        delete pTalkbackCore;
        delete pTalkbackNodeNext;
        m_tTalkbackNodeListLock.unlock();
        INFO_PRINT("addDeviceToTalkback fail as pTalkbackCore->initTalkback(parm) fail");
        return false;
    }
    if(tMode==TALKBACK_EXCLUSIVE){
        //独占模式
        //删除其他的对讲
        tagTalkbackNode *pTemp=m_pTalkbackNodeList;
        while(pTemp!=NULL){
            if(pTemp->pTalkbackCore!=NULL){
                pTemp->pTalkbackCore->deinitTalkback();
                delete pTemp->pTalkbackCore;
                pTemp->pTalkbackCore=NULL;
            }else{
                //do nothing
            }
            tagTalkbackNode *pNext=pTemp->pNext;
            delete pTemp;
            pTemp=pNext;
        }
        m_pTalkbackNodeList=NULL;
    }else{
        //共享模式
        removeDeviceFromTalkbackEx(parm);
    }
    tagTalkbackNode *pTemp=m_pTalkbackNodeList;
    while (pTemp!=NULL) {
        pTemp=pTemp->pNext;
    }
    pTemp=pTalkbackNodeNext;
    if(NULL==m_pTalkbackNodeList){
        m_pTalkbackNodeList=pTemp;
    }
    m_tTalkbackNodeListLock.unlock();
    return true;
}

bool TalkbackManager::removeDeviceFromTalkback(lpTalkbackContext parm)
{
    m_tTalkbackNodeListLock.lock();
    removeDeviceFromTalkbackEx(parm);
    m_tTalkbackNodeListLock.unlock();
    return true;
}

void TalkbackManager::clearTalkbackNodeList()
{
    m_tTalkbackNodeListLock.lock();
    tagTalkbackNode *pTemp=m_pTalkbackNodeList;
    while(pTemp!=NULL){
        if(pTemp->pTalkbackCore!=NULL){
            pTemp->pTalkbackCore->deinitTalkback();
            delete pTemp->pTalkbackCore;
            pTemp->pTalkbackCore=NULL;
        }else{
            //do nothing
        }
        tagTalkbackNode *pNext=pTemp->pNext;
        delete pTemp;
        pTemp=pNext;
    }
    m_pTalkbackNodeList=NULL;
    m_tTalkbackNodeListLock.unlock();
}

void TalkbackManager::removeDeviceFromTalkbackEx(lpTalkbackContext parm)
{
    if(m_pTalkbackNodeList==NULL){
        return ;
    }
    //fix me
    //第一步，移除非链表头的节点
    //第二步，判断链表头，是否需要移除
    TalkbackNode *pTempHead=m_pTalkbackNodeList;
    TalkbackNode *pTempNext=m_pTalkbackNodeList->pNext;
    while(NULL!=pTempNext){
        if(pTempNext->pTalkbackContext==parm){
            //find
            TalkbackNode *pRemove=pTempNext;
            if(pRemove->pTalkbackCore!=NULL){
                pRemove->pTalkbackCore->deinitTalkback();
                delete pRemove->pTalkbackCore;
            }
            pTempNext= pTempNext->pNext;
            pTempHead->pNext=pTempNext;
            delete pRemove;
        }else{
            //keep going
            pTempNext=pTempNext->pNext;
            pTempHead= pTempHead->pNext;
        }
    }
    if(m_pTalkbackNodeList->pTalkbackContext==parm){
        TalkbackNode *pRemove=m_pTalkbackNodeList;
        m_pTalkbackNodeList=pRemove->pNext;
        if(NULL!=pRemove->pTalkbackCore){
            pRemove->pTalkbackCore->deinitTalkback();
            delete pRemove;
        }
    }

}
