#include "y/core/tree/pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"

namespace Yttrium
{
    namespace Core
    {
        TreePool:: TreePool() noexcept
        {
        }

        TreePool:: ~TreePool() noexcept
        {
        }

        size_t TreePool:: count() const noexcept { return size; }
        

        void TreePool:: cache(const size_t n)
        {
            for(size_t i=n;i>0;--i)
            {
                store( new TreeNode(0,0,0) );
            }
        }

        void TreePool:: gc(const uint8_t amount) noexcept
        {
            TreeList list;
            PoolToList::Make(list,*this).sortByDecreasingAddress();
            {
                const size_t newSize = NewSize(amount,list.size);
                while(list.size>newSize) delete list.popHead();
            }
            ListToPool::Make(*this,list);
        };

    }

}
