#include "y/memory/workspace.hpp"
#include "y/core/pool.hpp"
#include "y/core/display.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include <ctime>

using namespace Yttrium;

namespace
{
    struct Node
    {
        size_t indx;
        Node * next;

        inline friend std::ostream & operator<<(std::ostream &os, const Node &node)
        {
            return os << node.indx;
        }
    };
}

Y_UTEST(core_pool)
{

    Core::Rand                 ran( (long) time(NULL) );
    Memory::Workspace<Node,10> wksp;
    Core::PoolOf<Node>         pool;

    const size_t N = wksp.Size;
    for(size_t i=1;i<=N;++i)
    {
        wksp[i].indx = i;
        Y_ASSERT(0==wksp[i].next);
    }

    Random::Shuffle(ran, &wksp[1], wksp.Size);
    Core::Display(std::cerr, &wksp[1], wksp.Size) << std::endl;

    std::cerr << pool << std::endl;
    for(size_t i=1;i<=N;++i)
    {
        pool.store( &wksp[i] );
        std::cerr << pool << std::endl;
    }
    while(pool.size)
    {
        pool.query();
        std::cerr << pool << std::endl;
    }


}
Y_UDONE()
