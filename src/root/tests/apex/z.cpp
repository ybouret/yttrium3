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

            Y_ASSERT( S == L+rhs );
            Y_ASSERT( S == lhs+R );

            { Integer Sum = L; Sum += R;   Y_ASSERT( S == Sum ); }
            { Integer Sum = L; Sum += rhs; Y_ASSERT( S == Sum ); }

            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( S == L+RN );
                { Integer Sum = L; Sum += RN; Y_ASSERT( S == Sum ); }
            }

            if(lhs>=0)
            {
                const Natural LN = (natural_t)lhs;
                Y_ASSERT( S == LN+R );

            }
        }
        for(apz i=-10;i<=10;++i) std::cerr << ' ' << i;
        std::cerr << std::endl;
        for(apz i=-10;i<=10;i++) std::cerr << ' ' << i;
        std::cerr << std::endl;
    }

    {
        std::cerr << "-- subtractions 64-bits" << std::endl;

        for(size_t iter=0;iter<1024;++iter)
        {
            const integer_t lhs    = ran.in<integer_t>(imin,imax);
            const integer_t rhs    = ran.in<integer_t>(imin,imax);
            const integer_t dif    = lhs - rhs;
            const Integer   L      = lhs;
            const Integer   R      = rhs;
            const Integer   D      = L-R; Y_ASSERT( D == dif );

            Y_ASSERT( D == L-rhs );
            Y_ASSERT( D == lhs-R );

            { Integer Dif = L; Dif -= R;   Y_ASSERT( D == Dif ); }
            { Integer Dif = L; Dif -= rhs; Y_ASSERT( D == Dif ); }


            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( D == L-RN );
                { Integer Dif = L; Dif -= RN; Y_ASSERT( D == Dif ); }
            }

            if(lhs>=0)
            {
                const Natural LN = (natural_t)lhs;
                Y_ASSERT( D == LN-R );
            }
        }

        for(apz i=10;i>=-10;--i) std::cerr << ' ' << i;
        std::cerr << std::endl;
        for(apz i=10;i>=-10;i--) std::cerr << ' ' << i;
        std::cerr << std::endl;
    }

    {
        std::cerr << "-- multiplications 64-bits" << std::endl;

        for(size_t iter=0;iter<1024;++iter)
        {
            const integer_t lhs    = ran.in<integer_t>(imin,imax);
            const integer_t rhs    = ran.in<integer_t>(imin,imax);
            const integer_t prod   = lhs * rhs;

            const Integer   L      = lhs;
            const Integer   R      = rhs;
            const Integer   P      = L*R; Y_ASSERT( P == prod );

            Y_ASSERT( P == L * rhs );
            Y_ASSERT( P == rhs * L );

            { Integer Prod = L; Prod *= R;   Y_ASSERT( Prod == prod ); }
            { Integer Prod = L; Prod *= rhs; Y_ASSERT( Prod == prod ); }



            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( P == L*RN );
                { Integer Prod = L; Prod *= RN; Y_ASSERT( Prod == prod ); }
            }

            if(lhs>=0)
            {
                const Natural LN = (natural_t)lhs;
                Y_ASSERT( P == LN*R );
            }

        }

    }

    {
        std::cerr << "-- divisions 64-bits" << std::endl;

        for(size_t iter=0;iter<1024;++iter)
        {
            const integer_t lhs    = ran.in<integer_t>(imin,imax);
            integer_t       rhs    = ran.in<integer_t>(imin,imax);
            while(!rhs) rhs = ran.in<integer_t>(imin,imax);
            const integer_t  q     = lhs/rhs;

            const Integer L = lhs;
            const Integer R = rhs;
            const Integer Q = lhs/rhs; Y_ASSERT(Q==q);

            Y_ASSERT( L/rhs == Q );
            Y_ASSERT( lhs/R == Q );

            { Integer Quot = L; Quot /= R;   Y_ASSERT(Q==Quot); }
            { Integer Quot = L; Quot /= rhs; Y_ASSERT(Q==Quot); }

            if(rhs>=0)
            {
                const Natural RN = (natural_t)rhs;
                Y_ASSERT( Q == L/RN );
                { Integer Quot = L; Quot /= RN; Y_ASSERT( Q == Quot ); }
            }

            if(lhs>=0)
            {
                const Natural LN = (natural_t)lhs;
                Y_ASSERT( Q == LN/R );
            }
        }

    }

    {
        std::cerr << "-- add/sub" << std::endl;
        for(size_t iter=0;iter<1024;++iter)
        {
            const apz lhs(ran, ran.in<size_t>(0,4000) );
            const apz rhs(ran, ran.in<size_t>(0,4000) );
            const apz sum = lhs + rhs;
            Y_ASSERT(sum - lhs == rhs);
            Y_ASSERT(sum - rhs == lhs);
        }
    }


    {
        std::cerr << "-- mul/div" << std::endl;
        for(size_t iter=0;iter<1024;++iter)
        {
            const apz lhs(ran, ran.in<size_t>(1,1000) );
            const apz rhs(ran, ran.in<size_t>(1,1000) );
            const apz prod = lhs * rhs;
            Y_ASSERT(prod/lhs==rhs);
            Y_ASSERT(prod/rhs==lhs);
        }
    }


}
Y_UDONE()

