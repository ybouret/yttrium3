
#include "y/counting/combination.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(counting_comb)
{

    for(size_t n=1;n<=8;++n)
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

    if(argc>2)
    {
        const size_t n = ASCII::Convert::To<size_t>(argv[1],"n",0);
        const size_t k = ASCII::Convert::To<size_t>(argv[2],"k",0);
        Combination  comb(n,k);
        std::cerr << "(" << n << "," << k << ") = " << comb.total << std::endl;
    }




}
Y_UDONE()


