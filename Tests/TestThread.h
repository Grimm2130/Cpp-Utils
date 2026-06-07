#if !defined(__TEST_THREAD_H__)
#define __TEST_THREAD_H__

#include "CppTemplates/ITest.h"
#include "Thread.h"
#include "Print.h"
#include <unistd.h>

namespace Tests
{
    namespace Utils
    {
        class Thread : public ITest
        {
        public:
            bool RunTests() override
            {
                ::Utils::Print::Info("Tests::Utils::Thread::RunTests()...");

                for( int i = 0; i < NumThreads; i++ )
                {
                    ::Utils::Thread& thread = mInstances[i];
                    thread.Run(this, Tester);
                }

                for( int i = 0; i < NumThreads; i++ )
                {
                    ::Utils::Thread& thread = mInstances[i];
                    thread.Join();
                }

                ::Utils::Print::Info("Tests::Utils::Thread::RunTests()...Done");

                return true;
            }

        private:
            static void* Tester( void * arg )
            {
                ::Utils::Print::Info("Thread[%ld]...Called 'tester'", pthread_self() );

                pthread_exit(NULL);
            }    

            static constexpr size_t NumThreads = 100;
            ::Utils::Thread mInstances[NumThreads];
        };
    } // namespace Utils
    
} // namespace Tests


#endif // __TEST_THREAD_H__
