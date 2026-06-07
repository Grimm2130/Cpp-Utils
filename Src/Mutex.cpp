#include "Mutex.h"
#include <memory.h>
#include <errno.h>

namespace Utils
{
    Mutex::Mutex( ) :
        mInitialized(false),
        mLastError(0)
    {
        if( pthread_mutex_init(&mInstance, NULL) == 0 )
        {
            mInitialized = true;
        }
    }

    Mutex::~Mutex()
    {
        if( mInitialized )
        {
            pthread_mutex_destroy(&mInstance);
            mInitialized = false;
        }
    }

    int Mutex::Lock()
    {
        mLastError = pthread_mutex_lock(&mInstance);
        return mLastError;
    }

    int Mutex::Unlock()
    {
        mLastError = pthread_mutex_unlock(&mInstance);
        return mLastError;
    }

    int Mutex::TryLock()
    {
        mLastError = pthread_mutex_trylock(&mInstance);
        return mLastError;
    }

    const int Mutex::GetLastError() const
    {
        return mLastError;
    }

    const char *Mutex::GetLastErrorStr() const
    {
        return strerror(mLastError);
    }

} // namespace Utils
