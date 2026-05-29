#include "y/apex/k/overseer.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(apex_overseer)
{
    Apex::Overseer & osi = Apex::Overseer::Instance();

    Y_PRINTV(osi.callSign());
    Y_PRINTV(Apex::Overseer::StaticBlockBytes);
    Y_SIZEOF(Apex::Overseer::StaticWords);
    
}
Y_UDONE()

