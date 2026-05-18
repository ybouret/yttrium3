
#include "y/core/htable.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(core_htable)
{

    for(size_t i=0;i<=32;++i)
    {
        Core::HTable htable(i,32);
        std::cerr << "#slots = " << std::setw(3) << i << " => " << htable.tsize << std::endl;
    }

}
Y_UDONE()

