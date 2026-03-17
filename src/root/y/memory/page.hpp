
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

           
        };
    }

}

#endif // !Y_Memory_Page_Included
