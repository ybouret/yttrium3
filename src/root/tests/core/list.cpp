
#include "y/memory/type/zombie.hpp"
#include "y/core/list.hpp"
#include "y/core/display.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include <ctime>
#include "y/type/sign.hpp"

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

        static inline int Compare(const Node * const lhs,
                                  const Node * const rhs) noexcept
        {
            return Sign::Of(lhs->indx,rhs->indx);
        }
    };

    template <typename NODE>
    static inline
    void fullCheck( const Core::ListOf<NODE> &list )
    {
        switch(list.size)
        {
            case 0:
                Y_CHECK(0==list.head);
                Y_CHECK(0==list.tail);
                return;

            case 1:
                Y_CHECK(list.head == list.tail);
                Y_CHECK(list.head->prev == 0);
                Y_CHECK(list.tail->next == 0);
                return;

            case 2:
                Y_CHECK(list.head != list.tail);
                Y_CHECK(list.head->prev == 0);
                Y_CHECK(list.tail->next == 0);
                Y_CHECK(list.head->next == list.tail);
                Y_CHECK(list.tail->prev == list.head);
                return;

            default:
                break;
        }

        Y_CHECK(list.size>=3);
        Y_CHECK(list.head != list.tail);
        Y_CHECK(list.head->prev == 0);
        Y_CHECK(list.tail->next == 0);
        Y_CHECK(list.head->next != list.tail);
        Y_CHECK(list.tail->prev != list.head);
        Y_CHECK(0!=list.head->next);
        Y_CHECK(0!=list.tail->prev);



    }


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
            Y_ASSERT( list.healthy() );
            {
                Core::ListOf<Node> lhs;
                {
                    Core::ListOf<Node> rhs;
                    list.divide(lhs,rhs);
                    Y_ASSERT(0==list.size);
                    //lhs.mergeTail(rhs);
                    //lhs.mergeHead(rhs);
                    if(ran.choice()) lhs.mergeTail(rhs); else lhs.mergeHead(rhs);
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

        for(size_t i=1;i<=N;++i)
        {
            if(ran.choice()) list.pushHead( &wksp[i] ); else list.pushTail( &wksp[i] );
        }
        std::cerr << list << std::endl;
        list.sort(Node::Compare);
        std::cerr << list << std::endl;
        while(list.size) list.popTail();


        for(size_t i=1;i<=N;++i)
        {
            Node * const node = &wksp[i];
            if(list.size<=0)
            {
                list.pushTail(node);
            }
            else
            {
                Node * const mine = list.fetch( ran.in<size_t>(1,list.size) );
                list.insertAfter(mine,node);
            }
            Y_ASSERT(i==list.size);
        }
        while(list.size) list.popTail();

        for(size_t i=1;i<=N;++i)
        {
            Node * const node = &wksp[i];
            if(list.size<=0)
            {
                list.pushTail(node);
            }
            else
            {
                Node * const mine = list.fetch( ran.in<size_t>(1,list.size) );
                list.insertBefore(mine,node);
            }
            Y_ASSERT(i==list.size);
        }

        std::cerr << list << std::endl;
        for(size_t i=N;i>=2;--i)
        {
            list.towardsHead( list.fetch(i) );
            std::cerr << list << std::endl;
        }

        while(list.size) list.popTail();

    }



}
Y_UDONE()
