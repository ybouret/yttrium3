#include "y/jive/pattern/leading.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(jive_leading)
{
    Jive::Leading lead;
    std::cerr << lead << std::endl;

    lead << 'A';
    std::cerr << lead << std::endl;
    lead << 'Z';
    std::cerr << lead << std::endl;
    lead.clr('Z');
    std::cerr << lead << std::endl;

    lead.set('0','9');
    std::cerr << lead << std::endl;



}
Y_UDONE()


