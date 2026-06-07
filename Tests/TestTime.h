#if !defined(__TEST_TIME_H__)
#define __TEST_TIME_H__

#include "CppTemplates/ITest.h"
#include "Print.h"
#include "Time.h"

namespace Tests
{
    namespace Utils
    {
        /// @brief Time
        class Time : public ITest
        {
        public:
            bool RunTests() override
            {
                ::Utils::Print::Info("Tests::Utils::Time::RunTests()");
                return TestTimeSeconds() && TestTimeMilliSeconds() && TestTimeMicroSeconds() && TestTimeNanoSeconds();
            }
        private:
        
            bool TestTimeSeconds()
            {
                ::Utils::Print::Info("Time in MicroSeconds: %lu", ::Utils::Time::GetSeconds() );
                return true;
            }

            bool TestTimeMilliSeconds()
            {
                ::Utils::Print::Info("Time in MicroSeconds: %lu", ::Utils::Time::GetMilliSeconds() );
                return true;
            }

            bool TestTimeMicroSeconds()
            {
                ::Utils::Print::Info("Time in MicroSeconds: %lu", ::Utils::Time::GetMicroSeconds() );
                return true;
            }

            bool TestTimeNanoSeconds()
            {
                ::Utils::Print::Info("Time in MicroSeconds: %lu", ::Utils::Time::GetNanoSeconds() );
                return true;
            }
        };
    } // namespace Time
    
} // namespace Tests


#endif // __TEST_TIME_H__
