#include "y/core/pool/to-list.hpp"
#include "y/core/pool/cxx.hpp"
#include "y/core/list/cxx.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Node
    {
    public:
        explicit Node(const size_t i) noexcept :
        indx(i), next(0), prev(0)
        {}

        virtual ~Node() noexcept
        {
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Node &node)
        {
            return os << node.indx;
        }

        size_t indx;
        Node * next;
        Node * prev;

    private:
        Y_Disable_Copy_And_Assign(Node);
    };
}

Y_UTEST(core_pool_and_list)
{
    CxxPool<Node> pool;
    CxxList<Node> list;



    for(size_t n=0;n<=10;++n)
    {
        for(size_t i=1;i<=n;++i)
        {
            pool.store( new Node(i) );
        }
        Y_ASSERT(n==pool.size);
        std::cerr << "pool=" << pool << " -> ";
        Core::PoolToList::Make(list,pool);
        std::cerr << list << std::endl;
        list.free();
    }
}

Y_UDONE()
