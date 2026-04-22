
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

}
Y_UDONE()
