#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(exception)
{
    {
        Exception excp("in %s",test);
        excp.display(std::cerr);
        excp << " now";
        excp.display(std::cerr);
        excp >> "and ";
        excp.display(std::cerr);
        excp.cat("%2.f",7.0f);
        excp.display(std::cerr);
        excp.pre("%d:",__LINE__);
        excp.display(std::cerr);
    }

    try {
        Specific::Exception excp("Testing","%s @ %s",test,__DATE__);
        excp.signedFor("my","data");
        throw excp;
    }
    catch(const Exception &excp)
    {
        excp.display(std::cerr);
    }

}

Y_UDONE()


