
//! \file

#ifndef Y_Memory_Page_Included
#define Y_Memory_Page_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct Page
        {

            Page *next;
            Page *prev;
            static Page *From(void * const blockAddr) noexcept;

            class Mill
            {
            protected:
                explicit Mill() noexcept;

            public:
                virtual ~Mill() noexcept;

                virtual Page * acquirePage(const unsigned shift) = 0;
                virtual void   releasePage(Page * const page, const unsigned shift) noexcept = 0;

            private:
                Y_Disable_Copy_And_Assign(Mill);
            };
        };
    }

}

#endif // !Y_Memory_Page_Included
