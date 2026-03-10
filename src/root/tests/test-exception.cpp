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
        throw Specific::Exception("Testing","%s @ %s",test,__DATE__);
    }
    catch(const Exception &excp)
    {
        excp.display(std::cerr);
    }

}

Y_UDONE()


