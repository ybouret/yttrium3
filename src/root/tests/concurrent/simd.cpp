#include "y/concurrent/api/simd/solo.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/type/temporary.hpp"
#include "y/utest/run.hpp"
#include "y/string/env/convert.hpp"


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

    static inline
    void DoSomething1( Concurrent::Context &context, const size_t & total )
    {
        size_t offset = 1;
        const size_t length = context.part(total,offset);


        {
            Y_Lock(context.sync);
            (std::cerr << "DoSomething1 in " << context << " with " << total << " : " << offset << "+" << length << std::endl).flush();
        }
    }

}


Y_UTEST(concurrent_simd)
{
    std::cerr << "-- entering " << test << std::endl;
    

    Concurrent::Solo solo;
    Concurrent::Crew crew( EnvironmentConvert::To<size_t>("NUM_THREADS",4) );



    solo(DoSomething);
    crew(DoSomething);

    const size_t total = 10;
    solo(DoSomething1,total);
    crew(DoSomething1,total);



    std::cerr << "-- leaving " << test << std::endl << std::endl;
}
Y_UDONE()

