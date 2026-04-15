#include "y/apex/integer.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_z)
{
    Core::Rand ran;
    const integer_t imin = -1000000000;
    const integer_t imax =  1000000000;

    {
        std::cerr << "-- comparisons 64-bits" << std::endl;

        for(size_t iter=0;iter<1024;++iter)
        {
            const integer_t lhs    = ran.in<integer_t>(imin,imax);
            const integer_t rhs    = ran.in<integer_t>(imin,imax);
            const Integer   L      = lhs;
            const Integer   R      = rhs;
            const SignType  result = Sign::Of(lhs,rhs);
            Y_ASSERT( result == Integer::Cmp(L,R) );
            Y_ASSERT( result == Integer::Cmp(L,rhs) );
            Y_ASSERT( result == Integer::Cmp(lhs,R) );

            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( result == Integer::Cmp(L,RN) );
            }

            if(lhs>=0)
            {
                const Natural LN = (natural_t)lhs;
                Y_ASSERT( result == Integer::Cmp(LN,R) );
             }
        }
    }

    {
        std::cerr << "-- additions 64-bits" << std::endl;

        for(size_t iter=0;iter<1024;++iter)
        {
            const integer_t lhs    = ran.in<integer_t>(imin,imax);
            const integer_t rhs    = ran.in<integer_t>(imin,imax);
            const integer_t sum    = lhs + rhs;
            const Integer   L      = lhs;
            const Integer   R      = rhs;
            const Integer   S      = L+R; Y_ASSERT( S == sum );

            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( S == L+RN );
            }
        }
    }

}
Y_UDONE()

