
#include "y/memory/pages.hpp"
#include "y/core/pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"
#include "y/memory/metrics.hpp"
#include "y/type/sign.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {

        Pages:: Pages(Page::Mill &pageMill, const unsigned blockShift) noexcept :
        pool(),
        pageShift(blockShift),
        pageBytes( size_t(1) << pageShift ),
        mill(pageMill)
        {
            assert(pageShift>=Metrics::MinPageShift);
            assert(pageShift<=Metrics::MaxPageShift);
        }

        void Pages:: release_() noexcept
        {
            while(pool.size) mill.releasePage( pool.query(), pageShift);
        }

        Pages:: ~Pages() noexcept
        {
            release_();
        }

        void Pages:: release() noexcept
        {
            release_();
        }

        size_t Pages:: count() const noexcept
        {
            return pool.size;
        }

        void Pages:: cache(const size_t n)
        {
            for(size_t i=0;i<n;++i) pool.store( mill.acquirePage(pageShift) );
        }


       

        void Pages:: gc(const uint8_t amount) noexcept
        {
            const size_t       newSize = NewSize(amount,pool.size);
            {
                Core::ListOf<Page> list;
                Core::PoolToList::Make(list,pool).sortByDecreasingAddress();
                while(list.size>newSize) mill.releasePage(list.popHead(),pageShift);
                Core::ListToPool::Make(pool,list);
            }
            assert(newSize==pool.size);

#if !defined(NDEBUG)
            for(const Page *page=pool.head;page;page=page->next)
            {
                assert(0==page->prev);
                if(page->next)
                {
                    assert(page->next <= page);
                }
            }
#endif // !defined(NDEBUG)
        }


        void * Pages:: get()
        {
            if(pool.size)
                return static_cast<Page *>( memset(pool.query(),0,pageBytes) );
            else
                return mill.acquirePage(pageShift);
        }

        void Pages:: put(void * const page) noexcept
        {
            assert(page);
            pool.store( Page::From(page) );
        }
    }

}

