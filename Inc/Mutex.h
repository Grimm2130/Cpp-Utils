#if !defined(__MUTEX_H__)
#define __MUTEX_H__

#include "CppTemplates/Templates.h"
#include <pthread.h>

namespace Utils
{
    class Mutex
    {
    public:
        Mutex();
        ~Mutex();
        int Lock();
        int Unlock();
        int TryLock();
        const int GetLastError() const ;
        const char *GetLastErrorStr() const;
    private:
        bool mInitialized;
        int mLastError;
        pthread_mutex_t mInstance;
    CLASS_IS_NON_COPYABLE(Mutex);
        friend class ConditionalVariable;
    };
} // namespace Utils


#endif // __MUTEX_H__
