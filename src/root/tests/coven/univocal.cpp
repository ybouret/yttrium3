
#include "y/coven/univocal.hpp"
#include "y/utest/run.hpp"
#include "y/container/cxx/array.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_univocal)
{
    Core::Rand    ran;

    for(size_t n=1;n<=7;++n)
    {
        std::cerr << "-- dimensions=" << n << std::endl;
        for(size_t iter=0;iter<3;++iter)
        {
            CxxArray<apz> array(n);

            for(size_t i=array.size();i>0;--i)
            {
                if( ran() > 0.6f )
                    array[i] = ran.in<int>(-4,4);
            }
            std::cerr << "\t" << array << std::endl;
            if(Coven::Univocal::Make(array))
            {
                std::cerr << "\t" << array << " [*]" << std::endl;
            }
            else
            {
                std::cerr << "nul vector..." << std::endl;
            }
            std::cerr << std::endl;
        }

    }

    for(size_t n=1;n<=7;++n)
    {
        std::cerr << "-- dimensions=" << n << std::endl;

        CxxArray<apz> target(n);
        CxxArray<apq> source(n);
        for(size_t iter=0;iter<3;++iter)
        {
            for(size_t i=source.size();i>0;--i)
            {
                if( ran() > 0.6f )
                    source[i] = apq(ran, ran.in<size_t>(0,8), ran.in<size_t>(1,8) );
                target[i] = -1;
            }
            std::cerr << "\t" << source << std::endl;
            Coven::Univocal::Make(target,source);
            std::cerr << "\t" << target << " [*]" << std::endl;
            std::cerr << std::endl;
        }

    }



}
Y_UDONE()
