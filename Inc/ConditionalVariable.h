#if !defined(__CONDITIONAL_VARIABLE_H__)
#define __CONDITIONAL_VARIABLE_H__

#include <pthread.h>
#include <cstdint>

namespace Utils
{
    class Mutex;

    class ConditionalVariable
    {
    public:
        ConditionalVariable();
        ~ConditionalVariable();
        int Signal();
        int Wait( Mutex& mutex );
        int Broadcast();
        int TimedWait( Mutex& mutex, long seconds, long nanoseconds );
        const int GetLastError() const ;
        const char *GetLastErrorStr() const;
    private:
        bool mInstantiated; 
        int mLastError;
        pthread_cond_t mInstance;
    };
} // namespace Utils


#endif // __CONDITIONAL_VARIABLE_H__
