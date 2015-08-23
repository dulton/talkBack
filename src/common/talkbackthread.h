#ifndef TALKBACKTHREAD_H
#define TALKBACKTHREAD_H

#ifdef WIN32
#include <windows.h>
#endif

#ifndef TALKBACK_THREAD_RET_TYPE
#ifdef WIN32
#define TALKBACK_THREAD_RET_TYPE DWORD
#else
#define TALKBACK_THREAD_RET_TYPE void *
#endif
#endif

#ifndef TALKBACK_THREAD_HANDLE

#ifdef WIN32
#define TALKBACK_THREAD_HANDLE HANDLE
#else
#define TALKBACK_THREAD_HANDLE pthread_t
#endif

#endif

#include "TalkBackDataTypeCommon.h"
class TalkbackThread
{
public:
    TalkbackThread();
    static void mSleep(int nTime);
    static talkback_int64 currentTime();
};

#endif // TALKBACKTHREAD_H
