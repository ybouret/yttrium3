
#include "y/memory/pages.hpp"
#include "y/memory/page/factory.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"
#include "y/memory/metrics.hpp"
#include "y/type/sign.hpp"
#include "y/ability/lockable.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {

        Pages:: Pages(PageFactory  & pageFactory,
                      Lockable     & userAccess,
                      const unsigned blockShift) noexcept :
        pool(),
        pageShift(blockShift),
        pageBytes( size_t(1) << pageShift ),
        factory(pageFactory),
        access(userAccess)
        {
            assert(pageShift>=Metrics::MinPageShift);
            assert(pageShift<=Metrics::MaxPageShift);
        }

        void Pages:: release_() noexcept
        {
            Y_Lock(access);
            while(pool.size) factory.releasePage( pool.query(), pageShift);
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
            Y_Lock(access);
            return pool.size;
        }

        void Pages:: cache(const size_t n)
        {
            Y_Lock(access);
            for(size_t i=0;i<n;++i) pool.store( factory.acquirePage(pageShift) );
        }


       

        void Pages:: gc(const uint8_t amount) noexcept
        {
            Y_Lock(access);
            const size_t       newSize = NewSize(amount,pool.size);
            {
                Core::ListOf<Page> list;
                Core::PoolToList::Make(list,pool).sortByDecreasingAddress();
                while(list.size>newSize) factory.releasePage(list.popHead(),pageShift);
                Core::ListToPool::Make(pool,list);
            }
            assert(newSize==pool.size);
            assert(pool.hasDecreasingAddresses());

#if 0
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
#endif
            
        }


        void * Pages:: get()
        {
            Y_Lock(access);
            if(pool.size)
                return static_cast<Page *>( memset(pool.query(),0,pageBytes) );
            else
            {
                return factory.acquirePage(pageShift);
            }
        }

        void Pages:: put(void * const page) noexcept
        {
            Y_Lock(access);
            assert(0!=page);
            pool.store( Page::From(page) );
        }
    }

}

