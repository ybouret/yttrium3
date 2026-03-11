
#include "y/memory/workspace.hpp"
#include "y/core/list.hpp"
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
        Node * prev;

        inline friend std::ostream & operator<<(std::ostream &os, const Node &node)
        {
            return os << node.indx;
        }
    };
}

Y_UTEST(core_list)
{

    Core::Rand                 ran( (long) time(NULL) );
    Memory::Workspace<Node,20> wksp;
    Core::ListOf<Node>         list;

    const size_t N = wksp.Size;
    for(size_t i=1;i<=N;++i)
    {
        wksp[i].indx = i;
        Y_ASSERT(0==wksp[i].next);
    }

    for(size_t iter=0;iter<10;++iter)
    {
        Random::Shuffle(ran, &wksp[1], wksp.Size);
        Core::Display(std::cerr, &wksp[1], wksp.Size) << std::endl;

        std::cerr << list << std::endl;
        for(size_t i=1;i<=N;++i)
        {
            if(ran.choice()) list.pushHead( &wksp[i] ); else list.pushTail( &wksp[i] );
            std::cerr << list << std::endl;
        }

        while(list.size)
        {
            if(ran.choice()) list.popTail(); else list.popHead();
            std::cerr << list << std::endl;
        }
    }



}
Y_UDONE()
