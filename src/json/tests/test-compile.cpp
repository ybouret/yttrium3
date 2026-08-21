#include "y/json/compiler.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(compile)
{
    JSON::Compiler json;

    if(argc>1)
    {
        JSON::Value jv;
        json( jv, Jive::Module::OpenFile(argv[1]) );
        std::cerr << jv << std::endl;
    }

}
Y_UDONE()

