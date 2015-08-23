#ifndef OFFERAUDIODATA_H
#define OFFERAUDIODATA_H

#include "offeraudiodata_global.h"
#include "TalkBackDataTypeCommon.h"
class OFFERAUDIODATASHARED_EXPORT OfferAudioData
{

public:
    explicit OfferAudioData();

    ~OfferAudioData();
    static bool checkClientIsSupportTalkback();
    static bool checkIsSupportSpecAudioCode(tagAudioCodeMode tCodeMode);
    static int  getSpecAudioCodeModeFrameBuffSize(tagAudioCodeMode tCodeMode);

    bool getData(void *parm,char *pBuff,int pBufferSize,int &nSize,talkback_int64 &nTimeStamp);
    bool applyAudio(void *parm,tagAudioCodeMode tCodeMode,AudioErrorCallback pErrorCallback);
    bool releaseAudio(void *parm);
private:

};

#endif // OFFERAUDIODATA_H
