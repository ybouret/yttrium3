//! \file

#ifndef Y_Associative_Book_Inluded
#define Y_Associative_Book_Inluded 1

#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{



    template <typename T>
    class BookEntry
    {
    public:
        Y_Args_Expose(T,Type);

        inline ~BookEntry() noexcept {}

    private:
        Y_Disable_Assign(BookEntry);
    };

}


#endif // !Y_Associative_Book_Inluded
