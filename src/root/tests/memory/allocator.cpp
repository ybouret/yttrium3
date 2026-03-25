#include "y/memory/allocator/global.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/dyadic.hpp"

#include "y/utest/run.hpp"


using namespace Yttrium;



Y_UTEST(memory_allocator)
{




    Concurrent::Singulet::Verbose = true;

    Memory::Dyadic &D = Memory::Dyadic::Instance();
    Memory::Global &G = Memory::Global::Instance();
    Memory::Pooled &P = Memory::Pooled::Instance();


    std::cerr << G.callSign() << "@" << G.lifeTime() << std::endl;
    std::cerr << P.callSign() << "@" << P.lifeTime() << std::endl;
    std::cerr << D.callSign() << "@" << D.lifeTime() << std::endl;


}
Y_UDONE()

