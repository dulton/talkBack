#include "TalkbackCInterface.h"
#include "TalkBackCommonTool.h"
#include "talkback.h"
#include "TalkBackDataTypeCommon.h"

#include "talkbacklock.h"
bool startTalkback(void *thiz){
    lpTalkbackContext parm=(lpTalkbackContext)thiz;
    if(NULL!=parm->pTalkbackContext){
        return ((Talkback*)parm->pTalkbackContext)->startTalkback(parm);
    }else{
        INFO_PRINT("startTalkback fail as parm->pTalkbackContext is null");
        return false;
    }
}
bool pauseTalkback(void * thiz){
    lpTalkbackContext parm=(lpTalkbackContext)thiz;
    if(NULL!=parm->pTalkbackContext){
        return ((Talkback*)parm->pTalkbackContext)->pauseTalkback(parm);
    }else{
        INFO_PRINT("pauseTalkback fail as parm->pTalkbackContext is null");
        return false;
    }
}

bool checkClientIsSupportTalkback(){
    return Talkback::checkClientIsSupportTalkback();
}

bool addDeviceToTalkback(void* thiz,int nMode,void *userContent,char*userName,char *password,char *url,char *ip,int nPort,void* errorEventHook){
    if(thiz==NULL){
       INFO_PRINT("addDeviceToTalkback fail as thiz is null");
       return false;
    }
    lpTalkbackContext parm=(lpTalkbackContext)thiz;
    parm->pUserContext=userContent;
    parm->nPort=nPort;
    parm->errorEventHook=(TalkbackInterfaceErrorCallback)errorEventHook;
    if(NULL==url||NULL==ip){
        INFO_PRINT("addDeviceToTalkback fail as url or ip is null");
        return false;
    }
    memcpy(parm->ip,ip,strlen(ip));
    memcpy(parm->url,url,strlen(url));
    if(userName!=NULL){
        memcpy(parm->userName,userName,strlen(userName));
    }
    if(password!=NULL){
        memcpy(parm->passWord,password,strlen(password));
    }
    tagTalkBackMode tMode =(tagTalkBackMode)nMode;
    Talkback * pTalkback=new Talkback;
    if(pTalkback->addDeviceToTalkback(parm,tMode)){
        parm->pTalkbackContext=pTalkback;
        INFO_PRINT("addDeviceToTalkback success");
        return true;
    }else{
        INFO_PRINT("addDeviceToTalkback fail as pTalkback->addDeviceToTalkback fail");
        pTalkback->removeDeviceFromTalkback(parm);
        delete pTalkback;
        return false;
    }
}
bool removeDeviceFromTalkback(void* thiz){
    lpTalkbackContext parm=(lpTalkbackContext)thiz;
    if(NULL!=parm->pTalkbackContext){
        ((Talkback*)parm->pTalkbackContext)->removeDeviceFromTalkback(parm);
        delete parm->pTalkbackContext;
        parm->pTalkbackContext=NULL;
    }else{
        INFO_PRINT("removeDeviceFromTalkback fail as parm->pTalkbackContext is null");
    }
    return true;
}
void*  initTalkback(){
    lpTalkbackContext thiz=new tagTalkbackContext;
    thiz->errorEventHook=NULL;
    memset(thiz->ip,0,sizeof(thiz->ip));
    memset(thiz->passWord,0,sizeof(thiz->passWord));
    thiz->nPort=0;
    memset(thiz->url,0,sizeof(thiz->url));
    memset(thiz->userName,0,sizeof(thiz->userName));
    thiz->pTalkbackContext=NULL;
    return thiz;
}
bool   deinitTalkback(void *thiz){
    if(thiz!=NULL){
        delete thiz;
        thiz=NULL;
    }
    return true;
}
