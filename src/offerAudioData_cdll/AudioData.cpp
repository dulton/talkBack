
#include"AudioData.h"
#include"TalkBackCommonTool.h"
#include "offeraudiodata.h"




bool checkClientIsSupportMicrophone()
{
    return OfferAudioData::checkClientIsSupportTalkback();
}


bool checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode)
{
    return OfferAudioData::checkIsSupportSpecAudioCode(tCodeMode);
}


int getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode)
{
    return OfferAudioData::getSpecAudioCodeModeFrameBuffSize(tCodeMode);
}


bool releaseAudio(tagAudioContext *pContext)
{
    if(pContext->pAudioDataContext!=NULL){
        OfferAudioData *pAudioDataObject=(OfferAudioData*)pContext->pAudioDataContext;
        if(pAudioDataObject->releaseAudio(pContext->pUserContext)){
            delete pAudioDataObject;
            pContext->pAudioDataContext=NULL;
            return true;
        }else{
            delete pAudioDataObject;
            pContext->pAudioDataContext=NULL;
            INFO_PRINT("releaseAudio fail as pAudioDataObject->releaseAudio fail");
            return false;
        }
    }else{
        return true;
    }
}


bool getData(tagAudioContext *pContext, char *pBuff, int nBuffSize, int &nSize,talkback_int64 &nTimeStamp)
{
    if(pContext->pAudioDataContext!=NULL){
        OfferAudioData *pAudioDataObject=(OfferAudioData*)pContext->pAudioDataContext;
        return pAudioDataObject->getData(pContext->pUserContext,pBuff,nBuffSize,nSize,nTimeStamp);
    }else{
        INFO_PRINT("getData fail as pAudioDataContext is NULL");
        return false;
    }
}


bool applyAudio(tagAudioContext *pContext, tagAudioCodeMode tCodeMode, AudioErrorCallback pErrorCallback)
{
    OfferAudioData* pAudioContext=new OfferAudioData;
    if(pAudioContext->applyAudio(pContext->pUserContext,tCodeMode,pErrorCallback)){
        pContext->pAudioDataContext=pAudioContext;
        return true;
    }else{
        //失败
        INFO_PRINT("applyAudio fail");
        pAudioContext->releaseAudio(pContext->pUserContext);
        delete pAudioContext;
        return false;
    }
}
