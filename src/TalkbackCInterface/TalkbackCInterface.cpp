#include "TalkbackCInterface.h"
#include "TalkBackCommonTool.h"
#include "talkback.h"

#include "talkbacklock.h"
bool startTalkback(lpTalkbackContext parm){
    if(NULL!=parm->pTalkbackContext){
        return ((Talkback*)parm->pTalkbackContext)->startTalkback(parm);
    }else{
        INFO_PRINT("startTalkback fail as parm->pTalkbackContext is null");
        return false;
    }
}
bool pauseTalkback(lpTalkbackContext parm){
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

bool addDeviceToTalkback(lpTalkbackContext parm,tagTalkBackMode tMode){
    Talkback * pTalkback=new Talkback;
    if(pTalkback->addDeviceToTalkback(parm,tMode)){
        parm->pTalkbackContext=pTalkback;
        return true;
    }else{
        INFO_PRINT("addDeviceToTalkback fail");
        pTalkback->removeDeviceFromTalkback(parm);
        delete pTalkback;
        return false;
    }
}
bool removeDeviceFromTalkback(lpTalkbackContext parm){
    if(NULL!=parm->pTalkbackContext){
        ((Talkback*)parm->pTalkbackContext)->removeDeviceFromTalkback(parm);
        delete parm->pTalkbackContext;
        parm->pTalkbackContext=NULL;
    }else{
        INFO_PRINT("removeDeviceFromTalkback fail as parm->pTalkbackContext is null");
    }
    return true;
}
