
#include "y/counting/combination.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(counting_comb)
{

    for(size_t n=1;n<=5;++n)
    {
        std::cerr << "-- n=" << n << std::endl;
        for(size_t k=1;k<=n;++k)
        {
            Combination comb(n,k);
            std::cerr << "-- \tk=" << k << std::endl;
            do {
                std::cerr << "\t\t" << comb << std::endl;
            } while (comb.next());
        }

    }




}
Y_UDONE()


