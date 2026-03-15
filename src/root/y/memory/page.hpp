
//! \file

#ifndef Y_Memory_Page_Included
#define Y_Memory_Page_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //! Memory Page layout
        //
        //______________________________________________________________________
        struct Page
        {
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Page *next; //!< for list/pool
            Page *prev; //!< for list

            //__________________________________________________________________
            //
            //
            // Functions
            //
            //__________________________________________________________________

            //! clear header part \param blockAddr anonymous block \return ready to use page
            static Page *From(void * const blockAddr) noexcept;

            //__________________________________________________________________
            //
            //
            //! Mill interface for power-of-two-sized pages
            //
            //__________________________________________________________________
            class Mill
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                explicit Mill() noexcept;

            public:
                virtual ~Mill() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! acquire a power of two page \param shift request \return 2^shift bytes
                virtual Page * acquirePage(const unsigned shift) = 0;

                //! release a power of two page \param page valid page \param shift for 2^shift bytes
                virtual void   releasePage(Page * const page, const unsigned shift) noexcept = 0;

            private:
                Y_Disable_Copy_And_Assign(Mill); //!< discarded
            };
        };
    }

}

#endif // !Y_Memory_Page_Included
