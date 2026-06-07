#if !defined(__SEMAPHORE_H__)
#define __SEMAPHORE_H__

#include <semaphore.h>
#include <cstdint>

namespace Utils
{
    class Semaphore
    {
    public:
        Semaphore( bool shared, const int value );
        ~Semaphore();
        int Wait();
        int TryWait();
        int TimedWait( long seconds, long nanoseconds );
        int Post();
        const int GetLastError() const ;
        const char *GetLastErrorStr() const;
    private:
        bool mShared;
        bool mInitialized;
        int mVal;
        int mLastError;
        sem_t mInstance;
    };
} // namespace Utils


#endif // __SEMAPHORE_H__
