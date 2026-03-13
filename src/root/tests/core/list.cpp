
#include "y/memory/zombie.hpp"
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
    Memory::Zombie<Node,30>    wksp;
    Core::ListOf<Node>         list;

    const size_t N = wksp.size;
    for(size_t i=1;i<=N;++i)
    {
        wksp[i].indx = i;
        Y_ASSERT(0==wksp[i].next);
    }

    for(size_t iter=0;iter<100;++iter)
    {
        Random::Shuffle(ran, &wksp[1], wksp.size);
        Core::Display(std::cerr, &wksp[1], wksp.size) << std::endl;

        std::cerr << list << std::endl;
        for(size_t i=1;i<=N;++i)
        {
            if(ran.choice()) list.pushHead( &wksp[i] ); else list.pushTail( &wksp[i] );
            std::cerr << list << std::endl;
            {
                Core::ListOf<Node> lhs;
                {
                    Core::ListOf<Node> rhs;
                    list.divide(lhs,rhs);
                    Y_ASSERT(0==list.size);
                    //lhs.mergeTail(rhs);
                    lhs.mergeHead(rhs);
                    //if(ran.choice()) lhs.mergeTail(rhs); else lhs.mergeHead(rhs);
                }
                list.swapForList(lhs);
            }
        }

        {
            size_t indx = 1;
            for(Node *node = list.head; node; node=node->next, ++indx)
            {
                Y_ASSERT(node == list.fetch(indx) );
            }
        }




        while(list.size)
        {
            switch( ran.in<int>(0,2) )
            {
                case 0: list.popTail(); break;
                case 1: list.popHead(); break;
                case 2: list.pop( list.fetch( ran.in<size_t>(1,list.size))); break;
            }
            std::cerr << list << std::endl;
        }
    }



}
Y_UDONE()
