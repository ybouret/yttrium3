#include "y/concurrent/api/simd/solo.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/type/temporary.hpp"
#include "y/utest/run.hpp"


#include "y/concurrent/thread.hpp"

using namespace Yttrium;



Y_UTEST(concurrent_simd)
{

    Concurrent::Solo solo;

    Concurrent::Crew crew(2);
    

    Y_SIZEOF(Concurrent::Thread);

}
Y_UDONE()

