
#include "y/calculus/prime/next.hpp"
#include "y/calculus/prime/prev.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/calculus/required-bits.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/core/hsort.hpp"

#include "y/utest/run.hpp"
using namespace Yttrium;

Y_UTEST(calculus_primes)
{
    Core::Rand ran;

    {
        std::cerr << "-- Looking For Primes..." << std::endl;
        Vector<uint64_t> p8;
        Vector<uint64_t> p16;

        uint64_t p = 0;
        size_t   n = 0;
        while(true)
        {
            p = Prime::Next(++p);
            ++n;
            const size_t pbits = RequiredBitsFor(p);
            std::cerr << std::setw(8) << p << " # " << std::setw(8) << n << " | bits=" << pbits << std::endl;

            if(pbits<=8) { p8 << p; continue; }
            if(pbits<=16) { Y_ASSERT(pbits>=9); p16 << p; continue; }

            break;
        }

        std::cerr << "p8=" << p8 << std::endl;
        std::cerr << "p16=" << p16 << std::endl;

        Y_PRINTV(p8.size());
        Y_PRINTV(p16.size());
    }

    {
        std::cerr << "HTable Primes" << std::endl;
        Vector<size_t> indices(WithAtLeast,5000);
        for(unsigned shift=2;shift<=12;++shift)
        {
            const size_t tableSize = size_t(1) << shift;
            const size_t tableMask = tableSize-1;
            const size_t tableIncr = Prime::Prev(tableSize);

            std::cerr << "tableSize=2^" << std::setw(2) << shift << " = " << std::setw(10) << tableSize << ", tableIncr=" << std::setw(10) << tableIncr << std::endl;

            for(size_t indx0=0;indx0<tableSize;++indx0)
            {
                size_t indx = indx0;
                indices.free();
                indices << indx;
                for(size_t i=0;i<tableMask;++i)
                {
                    (indx += tableIncr) &= tableMask;
                    indices << indx;
                }
                (indx += tableIncr) &= tableMask;
                Y_ASSERT(indx0==indx);
                Y_ASSERT(tableSize==indices.size());

                Core::HSort::Increasing( indices(), tableSize );
                for(size_t i=1;i<tableSize;++i)
                {
                    Y_ASSERT(i-1==indices[i]);
                }


            }

        }

    }



}
Y_UDONE()

