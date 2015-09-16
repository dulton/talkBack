#ifndef TALKBACKLOCK_H
#define TALKBACKLOCK_H

#ifdef WIN32

#include <windows.h>

#else
#include <pthread.h>
#endif
class TalkbackLock
{
public:
    TalkbackLock();
    ~TalkbackLock();
    void lock();
    void unlock();
private:

#ifdef WIN32
    CRITICAL_SECTION m_csLock;
#else
pthread_mutex_t m_csLock;
#endif
};

#endif // TALKBACKLOCK_H
