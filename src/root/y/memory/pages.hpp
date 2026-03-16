//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1


#include "y/memory/page.hpp"
#include "y/core/pool.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! LEVEL-1 cache of pages, THREAD-SAFE from mill's access()
        //
        //
        //______________________________________________________________________
        class Pages : public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param pageMill (thread-safe) peristent page allocator
             \param userLock persistent lock for this pages access
             \param shift    Metrics::MinPageShift <= shift <= Metrics::MaxPageShift
             */
            explicit Pages(Page::Mill &pageMill,
                           Lockable   &userLock,
                           const unsigned shift) noexcept;
            virtual ~Pages() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   release()         noexcept;
            virtual size_t count()     const noexcept;
            virtual void   cache(const size_t);
            virtual void   gc(const uint8_t) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void * get();                      //!< thread-unsafe allocation \return an existing or a new zeroed block
            void   put(void * const) noexcept; //!< thread-unsafe store a previously allocated page

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Core::PoolOf<Page>  pool;       //!< pool
        public:
            const unsigned      pageShift;  //!< in valid metrics boundaries
            const size_t        pageBytes;  //!< 2^pageShift
            Page::Mill        & mill;       //!< thread-safe, PERISTENT page provider
            Lockable          & lock;       //!< PERSISTEN mill.access()
            
        private:
            Y_Disable_Copy_And_Assign(Pages); //!< discarded
            void release_() noexcept;         //!< release pages pool
        };

    }

}

#endif // !Y_Memory_Pages_Included
