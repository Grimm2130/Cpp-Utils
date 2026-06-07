#if !defined(__THREAD_H__)
#define __THREAD_H__

#include "CppTemplates/Templates.h"
#include <pthread.h>
#include <atomic>

typedef void* (*ThreadFuncPtr)(void*);
typedef void* ThreadArg;

namespace Utils
{
    class Thread
    {
    public:
        Thread( bool isCancellable = true, bool isJoinable = true );
        ~Thread();
        int Run( const ThreadArg arg, const ThreadFuncPtr func );
        int Join();
        int Cancel();
        const int GetLastError() const ;
        const char *GetLastErrorStr() const;
    private:
    
        
        /// @brief Thread context object
        struct ThreadContext
        {
            Thread& mThread;
            ThreadArg mArg;
            ThreadFuncPtr mTask;
            ThreadContext( Thread& thread ) : mThread(thread), mArg(nullptr), mTask(nullptr) {};
            private:
            CLASS_IS_NON_COPYABLE(ThreadContext);
        };
    
        static void* ThreadEntry( void* context );
        
        const bool mIsJoinable;
        const bool mIsCancellable;
        std::atomic_bool mIsRunning;
        std::atomic_bool mHasReturned;
        int mLastError;
        ThreadContext mContext;
        pthread_t mInstance;
    CLASS_IS_NON_COPYABLE(Thread)
    };
} // namespace Utils


#endif // __THREAD_H__
