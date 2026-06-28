
#include "y/chemical/reactive/equilibrium/db.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Chemical;

Y_UTEST(db)
{
    for(size_t i=0;i<EDB::Count;++i)
    {
        std::cerr << EDB::Table[i] << std::endl;
    }

}
Y_UDONE()

