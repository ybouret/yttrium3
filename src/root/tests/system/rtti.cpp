#include "y/system/rtti.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_rtti)
{
    RTTI &f = RTTI::Of<float>();

    Y_PRINTV(f);
    Y_PRINTV( f.aka("f") );
    Y_PRINTV( f.aka("float") );


    Y_PRINTV( RTTI::Make<size_t>("size_t") );
    Y_PRINTV( RTTI::CXX<double>() );
    std::cerr << std::endl;

    RTTI::List L;
    RTTI::Collect(L);
    std::cerr << "RTTI:" << std::endl;
    for(const RTTI::List::NodeType *node=L->head;node;node=node->next)
    {
        std::cerr << "-- " << **node << std::endl;
    }
}
Y_UDONE()

