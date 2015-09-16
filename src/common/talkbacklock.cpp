#include "talkbacklock.h"

TalkbackLock::TalkbackLock()
{
#ifdef WIN32
    InitializeCriticalSection(&m_csLock);
#else
    m_csLock=PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&m_csLock,NULL);
#endif

}

TalkbackLock::~TalkbackLock()
{
#ifdef WIN32
    DeleteCriticalSection(&m_csLock);
#else
    pthread_mutex_destroy(&m_csLock);
#endif
}

void TalkbackLock::lock()
{
#ifdef WIN32
    EnterCriticalSection(&m_csLock);
#else
    pthread_mutex_lock(&m_csLock);
#endif
}

void TalkbackLock::unlock()
{
#ifdef WIN32
    LeaveCriticalSection(&m_csLock);
#else
   pthread_mutex_unlock(&m_csLock);
#endif
}
