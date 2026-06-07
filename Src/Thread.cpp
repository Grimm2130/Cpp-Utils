#include "Thread.h"
#include "Print.h"
#include <string.h>

namespace Utils
{
    Thread::Thread( bool isCancellable, bool isJoinable ) :
        mIsRunning(false),
        mIsCancellable(isCancellable),
        mIsJoinable(isJoinable),
        mHasReturned( !isJoinable ),
        mLastError(0),
        mContext(*this)
    {
    }

    Thread::~Thread()
    {
        if( !mIsRunning && mHasReturned )
        {
            mContext.mArg = nullptr;
            mContext.mTask = nullptr;
        }
    }

    int Thread::Run( const ThreadArg arg, const ThreadFuncPtr func )
    {
        if( mIsRunning == false )
        {
            mContext.mArg = arg;
            mContext.mTask = func;
            pthread_attr_t attr;
            
            pthread_attr_init(&attr);
    
            if( mIsJoinable == false )
            {
                mLastError = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
            }
    
            if( mLastError == 0 )
            {
                mLastError = pthread_create( &mInstance, &attr, ThreadEntry, (void*)(&mContext) );

                if( mLastError != 0 )
                {
                    Print::Error("Thread creation failed...");
                }
            }
    
            pthread_attr_destroy(&attr);
        }

        return mLastError;
    }

    void* Thread::ThreadEntry( void* context )
    {        
        ThreadContext* contextPtr = static_cast<ThreadContext*>(context);

        contextPtr->mThread.mIsRunning = true;

        if(contextPtr->mThread.mIsCancellable == false )
        {
            contextPtr->mThread.mLastError = pthread_setcancelstate( PTHREAD_CANCEL_DISABLE, NULL );
        }

        contextPtr->mTask(contextPtr->mArg);

        contextPtr->mThread.mIsRunning = false;

        contextPtr->mThread.mHasReturned = true;

        return nullptr;
    }

    int Thread::Join()
    {
        if( mIsJoinable )
        {
            mLastError = pthread_join(mInstance, NULL);
            
            if( mLastError == 0 )
            {
                mHasReturned = true;
            }
            else
            {
                Print::Error("Thread Failed on Join::%s\n", GetLastErrorStr() );
            }
        }
        return mLastError;
    }

    int Thread::Cancel()
    {
        if( mIsCancellable )
        {
            mLastError = pthread_cancel( mInstance );
        }
        return mLastError;
    }

    const int Thread::GetLastError() const 
    {
        return mLastError;
    }

    const char *Thread::GetLastErrorStr() const
    {
        return strerror(mLastError);
    }

} // namespace Utils
