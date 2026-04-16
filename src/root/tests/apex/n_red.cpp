
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_n_red)
{

    for(int i=1;i<argc;++i)
    {
        for(int j=1;j<argc;++j)
        {
            Natural lhs = (natural_t)atoi(argv[i]);
            Natural rhs = (natural_t)atoi(argv[j]);
            std::cerr << lhs << ":" << rhs << " => ";
            Natural::Reduce(lhs,rhs);
            std::cerr << lhs << ":" << rhs;
            std::cerr << std::endl;
        }
    }

}
Y_UDONE()

