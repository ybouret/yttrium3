#include "y/object/light/factory.hpp"
#include "y/utest/run.hpp"
#include "y/utest/memio.hpp"


using namespace Yttrium;

Y_UTEST(light_object)
{

    Concurrent::Singulet::Verbose = true;
    Core::Rand ran;

    Y_PRINTV(LightObject::Factory::TableSize);
    Y_SIZEOF(LightObject::Factory::Node);


    UTest::MemIO::Test<LightObject,512,16>(ran,80);

    LightObject::Factory &F = LightObject::Factory::Instance();
    F.writeXML(std::cerr);

}
Y_UDONE()


