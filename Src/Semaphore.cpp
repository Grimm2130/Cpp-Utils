#include "Semaphore.h"
#include "Time.h"
#include <cerrno>
#include <cstring>
#include <ctime>

namespace Utils
{
        Semaphore::Semaphore( bool shared, const int value ) :
            mShared(shared),
            mInitialized(false),
            mVal(value),
            mLastError(0)
        {
            if((mLastError = sem_init( &mInstance, int(mShared), mVal )) == 0 )
            {
                mInitialized = true;
            }
            else
            {
                mLastError = errno;
            }
        }

        Semaphore::~Semaphore()
        {
            if( mInitialized )
            {
                sem_destroy( &mInstance );
            }
        }

        
        int Semaphore::Wait()
        {
            if( mInitialized )
            {
                mLastError = sem_wait(&mInstance);
            }
            return mLastError;
        }

        int Semaphore::TryWait()
        {
            if( mInitialized )
            {
                mLastError = sem_trywait(&mInstance);
            }
            return mLastError;
        }

        int Semaphore::TimedWait( long seconds, long nanoseconds  )
        {
            if( mInitialized )
            {
                TimeSpec time = {.tv_sec = seconds, .tv_nsec = nanoseconds };
                mLastError = sem_timedwait( &mInstance, &time );
            }

            return mLastError;
        }

        int Semaphore::Post()
        {
            if( mInitialized )
            {
                mLastError = sem_post(&mInstance);
            }
            return mLastError;
        }

        const int Semaphore::GetLastError() const
        {
            return mLastError;
        }

        const char *Semaphore::GetLastErrorStr() const
        {
            return strerror(mLastError);
        }

} // namespace Utils
