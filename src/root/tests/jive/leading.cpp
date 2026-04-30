#include "y/jive/pattern/leading.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


namespace
{

}

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

    lead.set( Jive::Within('0','9') );
    std::cerr << lead << std::endl;


    lead.ldz();
    std::cerr << lead << std::endl;

    lead.all();
    std::cerr << lead << std::endl;

    lead.clr('X');
    std::cerr << lead << std::endl;



}
Y_UDONE()


