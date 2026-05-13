#include "y/utest/run.hpp"
#include "y/ascii/printable.hpp"

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
        throw excp.signedFor("my","data");
    }
    catch(const Exception &excp)
    {
        excp.display(std::cerr);
    }

    Exception X("%s%s%s",
                ASCII::Printable::Text('\t'),
                ASCII::Printable::Text('\n'),
                ASCII::Printable::Char[0xf4]);
    X.display(std::cerr);

}

Y_UDONE()


