#include "talkbackthread.h"

#ifdef WIN32
#include <time.h>
#else

#endif

#ifdef WIN32
#define LOCALTIME_R(T) localtime((T))
#else
#define LOCALTIME_R(T) localtime_r((T),(struct tm *)&tmres)
#endif

TalkbackThread::TalkbackThread()
{
}



void TalkbackThread::mSleep(int nTime)
{
#ifdef WIN32
    Sleep(nTime);
#else
    usleep(nTime*1000);
#endif
}
long long TalkbackThread::currentTime()
{
    //fix me
    talkback_int64 tCurrentTime=0;
    struct   tm   *tmNow;
    time_t   long_time;
    time(&long_time);
    tCurrentTime=long_time;
    tmNow   =   LOCALTIME_R(   &long_time   );
#ifdef WIN32
    struct timeb tp;
    ftime(&tp);
    tCurrentTime=tp.millitm+tp.time*1000;
#else
    struct timeval tmv;
    gettimeofday(&tmv,NULL);
    tCurrentTime=tmv.usec/1000;
#endif
    return tCurrentTime;
}
