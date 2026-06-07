#include "ConditionalVariable.h"
#include "Mutex.h"
#include "Time.h"
#include <cerrno>
#include <cstring>
#include <ctime>

namespace Utils
{
        ConditionalVariable::ConditionalVariable() :
            mInstantiated(false),
            mLastError(0)
        {
            if( (mLastError = pthread_cond_init( &mInstance, NULL)) == 0 )
            {
                mInstantiated = true;
            }
        }

        ConditionalVariable::~ConditionalVariable()
        {
            if( mInstantiated )
            {
                pthread_cond_destroy( &mInstance );
                mInstantiated = false;
            }
        }

        int ConditionalVariable::Signal()
        {
            if( mInstantiated )
            {
                mLastError = pthread_cond_signal(&mInstance);
            }
            return mLastError;
        }

        int ConditionalVariable::Wait( Mutex& mutex )
        {
            if( mInstantiated )
            {
                mLastError = pthread_cond_wait(&mInstance, &mutex.mInstance);
            }
            return mLastError;
        }

        int ConditionalVariable::Broadcast()
        {
            if( mInstantiated )
            {
                mLastError = pthread_cond_broadcast(&mInstance);
            }
            return mLastError;
        }

        int ConditionalVariable::TimedWait( Mutex& mutex, long seconds, long nanoseconds )
        {
            if( mInstantiated )
            {
                TimeSpec time = {.tv_sec = seconds, .tv_nsec = nanoseconds };
                mLastError = pthread_cond_timedwait( &mInstance, &mutex.mInstance, &time );
            }
            
            return mLastError;
        }

        const int ConditionalVariable::GetLastError() const
        {
            return mLastError;
        }

        const char *ConditionalVariable::GetLastErrorStr() const
        {
            return strerror(mLastError);
        }

} // namespace Utils
