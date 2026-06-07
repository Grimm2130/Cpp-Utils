#include "TestTime.h"
#include "TestThread.h"
#include "TestMutex.h"


int main(int argc, char const *argv[])
{

    Utils::Print::Info("Running Tests for all Utility modules...");
    
    Tests::Utils::Time timeTests;

    if( timeTests.RunTests() )
    {
        // next
        Tests::Utils::Thread threadTests;
        if( threadTests.RunTests() )
        {
            Tests::Utils::Mutex mutexTests;
            if( mutexTests.RunTests() )
            {
                
            }
        }
    }

    Utils::Print::Info("Running Tests for all Utility modules...Done");
    return 0;
}
