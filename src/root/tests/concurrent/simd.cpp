#include "y/concurrent/api/simd/solo.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/type/temporary.hpp"
#include "y/utest/run.hpp"


#include "y/concurrent/thread.hpp"

using namespace Yttrium;


namespace
{
    static inline
    void DoSomething( Concurrent::Context &context )
    {
        {
            Y_Lock(context.sync);
            (std::cerr << "DoSomething in " << context << std::endl).flush();
        }
    }
}


Y_UTEST(concurrent_simd)
{
    std::cerr << "-- entering " << test << std::endl;
    

    Concurrent::Solo solo;
    Concurrent::Crew crew(2);


    Y_SIZEOF(Concurrent::Thread);

    solo(DoSomething);
    crew(DoSomething);


    std::cerr << "-- leaving " << test << std::endl << std::endl;
}
Y_UDONE()

