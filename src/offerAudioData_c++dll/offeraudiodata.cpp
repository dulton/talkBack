#include "offeraudiodata.h"
#include "audiocode.h"
#include "talkbacklock.h"

static TalkbackLock g_csAudioCodeLock;
static int g_nAudioCodeCount=0;
static AudioCode *g_pAudioCode=NULL;
void applyAudioCode(){
    g_csAudioCodeLock.lock();
    if(g_nAudioCodeCount==0){
        g_pAudioCode=new AudioCode;
        g_pAudioCode->initAudio();
        g_nAudioCodeCount++;
    }else{
        g_nAudioCodeCount++;
    }
    g_csAudioCodeLock.unlock();
}
void releaseAudioCode(){
    g_csAudioCodeLock.lock();
    if(g_nAudioCodeCount>0){
        g_nAudioCodeCount=g_nAudioCodeCount-1;
        if(g_nAudioCodeCount==0){
            g_pAudioCode->deinitAudio();
            delete g_pAudioCode;
            g_pAudioCode=NULL;
        }else{
            //do nothing
        }
    }else{
            //do nothing
    }
    g_csAudioCodeLock.unlock();
}
OfferAudioData::OfferAudioData()
{
    applyAudioCode();
}

OfferAudioData::~OfferAudioData()
{
    releaseAudioCode();
}

bool OfferAudioData::checkClientIsSupportTalkback()
{
    return AudioCode::checkClientIsSupportTalkback();
}

bool OfferAudioData::checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode)
{
    return AudioCode::checkIsSupportSpecAudioCode(tCodeMode);
}

int OfferAudioData::getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode)
{
    return AudioCode::getSpecAudioCodeModeFrameBuffSize(tCodeMode);
}

bool OfferAudioData::getData(void *parm, char *pBuff, int nBufferSize, int &nSize,talkback_int64 &nTimeStamp)
{
    return g_pAudioCode->getData(parm,pBuff,nBufferSize,nSize,nTimeStamp);
}

bool OfferAudioData::applyAudio(void *parm, tagAudioCodeMode tCodeMode, AudioErrorCallback pErrorCallback)
{
    return g_pAudioCode->applyAudio(parm,tCodeMode,pErrorCallback);
}

bool OfferAudioData::releaseAudio(void *parm)
{
    return g_pAudioCode->releaseAudio(parm);
}



