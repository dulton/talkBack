#include "talkbacklock.h"

TalkbackLock::TalkbackLock()
{
#ifdef WIN32
    InitializeCriticalSection(&m_csLock);
#else

#endif

}

TalkbackLock::~TalkbackLock()
{
#ifdef WIN32
    DeleteCriticalSection(&m_csLock);
#else

#endif
}

void TalkbackLock::lock()
{
#ifdef WIN32
    EnterCriticalSection(&m_csLock);
#else

#endif
}

void TalkbackLock::unlock()
{
#ifdef WIN32
    LeaveCriticalSection(&m_csLock);
#else

#endif
}
