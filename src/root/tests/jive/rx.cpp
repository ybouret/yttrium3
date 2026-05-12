
#include "y/jive/regexp.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;


Y_UTEST(jive_rx)
{

    if(argc>1)
    {
        AutoPtr<Jive::Pattern> p = Jive::RegExp::Compile(argv[1],0);

    }


}
Y_UDONE()
