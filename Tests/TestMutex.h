#include "CppTemplates/ITest.h"
#include "Mutex.h"
#include "Thread.h"
#include "Print.h"

namespace Tests
{
    namespace Utils
    {
        class Mutex : public ::Tests::ITest
        {
        public:
            Mutex() :
                mCount(0),
                mMutex(new ::Utils::Mutex)
            {
            }
            ~Mutex()
            {
                delete mMutex;
            }

            bool RunTests() override
            {
                ::Utils::Print::Info("Tests::Utils::Mutex...");
                bool res = TestCounter();
                ::Utils::Print::Info("Tests::Utils::Mutex...Done");
                return res;
            }
        private:
        
            bool TestCounter()
            {
                bool res;

                ::Utils::Print::Info("Tests::Utils::Mutex::TestCounter()...");

                for( int i = 0; i < NumThreads; i++ )
                {
                    ::Utils::Thread& thread = mThreads[i];
                    thread.Run(this, Counter);
                }
                for( int i = 0; i < NumThreads; i++ )
                {
                    ::Utils::Thread& thread = mThreads[i];
                    thread.Join();
                }

                if( mCount == (NumIters * NumThreads))
                {
                    ::Utils::Print::Info("Tests::Utils::Mutex::TestCounter()...Passed");
                    res = true;
                }
                else
                {
                    ::Utils::Print::Info("Tests::Utils::Mutex::TestCounter()...Failed. Actual(%lu) != Expected(%u)",
                        mCount,
                        (NumIters * NumThreads)
                    );
                    res = false;
                }

                return res;
            }

            static void* Counter(void* arg)
            {
                Mutex* mutexTester = static_cast<Mutex*>(arg);

                for( int i = 0; i < Mutex::NumIters; i++ )
                {
                    mutexTester->mMutex->Lock();
                    mutexTester->mCount++;
                    mutexTester->mMutex->Unlock();
                }

                pthread_exit(NULL);
            }

            static constexpr size_t NumThreads = 100;
            static constexpr size_t NumIters = 1000;
            size_t mCount;
            ::Utils::Mutex *mMutex;
            ::Utils::Thread mThreads[NumThreads];
        };

    } // namespace Utils
    
} // namespace Tests
