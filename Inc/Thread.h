#if !defined(__THREAD_H__)
#define __THREAD_H__

#include "CppTemplates/Templates.h"
#include <pthread.h>

typedef void (*ThreadFuncPtr)(void*);
typedef void* ThreadArg;

namespace Utils
{
    
    struct ThreadContext
    {
        ThreadArg mArg;
        ThreadFuncPtr mTask;
        ThreadContext() : mArg(nullptr), mTask(nullptr) {};
    private:
        CLASS_IS_NON_COPYABLE(ThreadContext);
    };

    class Thread
    {
        Thread( bool isCancellable, bool isJoinable );
        ~Thread();
        int Run( const ThreadContext& );
        int Join();
        int Cancel();
    private:
        bool mInstantiated;
        bool mIsRunning;
        bool mIsJoinable;
        bool mIsCancellable;
        pthread_t mInstance;
    CLASS_IS_NON_COPYABLE(Thread)
    };
} // namespace Utils


#endif // __THREAD_H__
