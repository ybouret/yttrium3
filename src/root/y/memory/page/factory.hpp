
//! \file

#ifndef Y_Memory_Page_Factory_Included
#define Y_Memory_Page_Factory_Included 1


#include "y/memory/page.hpp"

namespace Yttrium
{

    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Interface for thread-safe, power-of-two-sized pages
        //
        //
        //______________________________________________________________________
        class PageFactory
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit PageFactory() noexcept;

        public:
            virtual ~PageFactory() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! acquire a power of two page
            /**
             - the call MUST be THREAD-SAFE
             \param shift request
             \return 2^shift bytes
             */
            virtual Page * acquirePage(const unsigned shift) = 0;

            //! release a power of two page
            /**
             - the call MUST be THREAD-SAFE  
             \param page valid, previously acquired page
             \param shift for 2^shift bytes
             */
            virtual void   releasePage(Page * const page, const unsigned shift) noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(PageFactory); //!< discarded
        };
    }

}

#endif // !Y_Memory_Page_Factory_Included

