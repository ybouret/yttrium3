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

        inline explicit BookEntry(ConstType &args) noexcept :
        data(args),
        key_(data)
        {
        }

        inline BookEntry(const BookEntry &other) noexcept :
        data(other.data),
        key_(other.key_)
        {
        }
        
        inline ~BookEntry() noexcept {}

        inline const AddrKey & key() const noexcept { return key_; }

    private:
        Y_Disable_Assign(BookEntry);
        ConstType    & data;
        const AddrKey  key_;
    };

}


#endif // !Y_Associative_Book_Inluded
