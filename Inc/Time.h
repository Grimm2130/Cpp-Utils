#if !defined(__TIME_H__)
#define __TIME_H__

#include "CppTemplates/Templates.h"
#include <cstdint>
#include <ctime>

typedef struct timespec TimeSpec;

namespace Utils
{
    class Time
    {
    private:

    public:

        inline const TimeSpec GetTime()
        {
            TimeSpec time;
            clock_gettime(CLOCK_MONOTONIC, &time);
            return time;
        }

        inline uint64_t GetSeconds()
        {
            TimeSpec time;
            clock_gettime(CLOCK_MONOTONIC, &time);
            return time.tv_sec;
        }

        inline uint64_t GetMilliSeconds()
        {
            TimeSpec time;
            clock_gettime(CLOCK_MONOTONIC, &time);
            return (time.tv_sec * 1E3) + (time.tv_nsec / 1E6);
        }

        inline uint64_t GetMicroSeconds()
        {
            TimeSpec time;
            clock_gettime(CLOCK_MONOTONIC, &time);
            return (time.tv_sec * 1E6) + (time.tv_nsec / 1E3);
        }

        inline uint64_t GetNanoSeconds()
        {
            TimeSpec time;
            clock_gettime(CLOCK_MONOTONIC, &time);
            return (time.tv_sec * 1E9) + time.tv_nsec;
        }

    private:

    CLASS_IS_STATIC_ONLY(Time)
    };
} // namespace Utils


#endif // __TIME_H__
