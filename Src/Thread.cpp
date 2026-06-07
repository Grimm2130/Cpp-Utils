#include "Thread.h"
#include <string.h>

namespace Utils
{
    Thread::Thread( bool isCancellable, bool isJoinable ) :
        mIsRunning(false),
        mIsCancellable(isCancellable),
        mIsJoinable(isJoinable),
        mHasReturned( !isJoinable ),
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
        mContext.mArg = arg;
        mContext.mTask = func;
        pthread_attr_t attr;

        if( mIsJoinable == false )
        {
            mLastError = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
        }

        if( mLastError == 0 )
        {
            mLastError = pthread_create( &mInstance, &attr, ThreadEntry, (void*)(&mContext) );
        }

        return mLastError;
    }

    void* Thread::ThreadEntry( void* context )
    {        
        ThreadContext* contextPtr = static_cast<ThreadContext*>(context);

        contextPtr->mThread.mIsRunning = true;

        if(contextPtr->mThread.mIsCancellable )
        {
            contextPtr->mThread.mLastError = pthread_setcancelstate( PTHREAD_CANCEL_DISABLE, NULL );
        }

        contextPtr->mTask(contextPtr->mArg);

        contextPtr->mThread.mIsRunning = false;

        pthread_exit(NULL);
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
