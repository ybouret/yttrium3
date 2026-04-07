#include "y/object/light/factory.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"

using namespace Yttrium;

Y_UTEST(light_object)
{

    Concurrent::Singulet::Verbose = true;
    Core::Rand ran;

    Y_PRINTV(LightObject::Factory::TableSize);
    Y_SIZEOF(LightObject::Factory::Node);

    LightObject::Factory &F = LightObject::Factory::Instance();

    {
        void * addr = F.acquire(17);
        Random::FillWith(ran,addr,17);
        F.release(addr,17);
    }

    F.writeXML(std::cerr);

}
Y_UDONE()


