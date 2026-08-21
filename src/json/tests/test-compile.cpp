#include "y/json/compiler.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(compile)
{
    JSON::Compiler json;

    if(argc>1)
    {
        json( Jive::Module::OpenFile(argv[1]) );
    }

}
Y_UDONE()

