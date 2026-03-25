//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1


#include "y/memory/page.hpp"
#include "y/core/pool.hpp"
#include "y/ability/caching.hpp"
#include "y/ability/logging.hpp"

namespace Yttrium
{
    class Lockable;
    
    namespace Memory
    {
        class PageFactory;

        //______________________________________________________________________
        //
        //
        //
        //! LEVEL-1 cache of pages, THREAD-SAFE, autonomous
        //
        //
        //______________________________________________________________________
        class Pages : public Caching, public Logging
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup to manage pages of 2^shift bytes
            /**
             \param pageFactory (thread-safe) peristent page factory
             \param userAccess  PERSISTENT lock for this access
             \param shift       Metrics::MinPageShift <= shift <= Metrics::MaxPageShift
             */
            explicit Pages(PageFactory &  pageFactory,
                           Lockable    &  userAccess,
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
            virtual void   toXML(XML::Log &) const;
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void * get();                      //!< thread-safe allocation \return an existing or a new zeroed block
            void   put(void * const) noexcept; //!< thread-safe store a previously allocated page

            //! access \return &pool
            const Core::Linked<Page> * operator->() const noexcept;

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
            PageFactory       & factory;    //!< thread-safe, PERISTENT page factory
            Lockable          & access;     //!< PERSISTENT access lock

        private:
            Y_Disable_Copy_And_Assign(Pages); //!< discarded
            void release_() noexcept;         //!< release pages pool
        };

    }

}

#endif // !Y_Memory_Pages_Included
