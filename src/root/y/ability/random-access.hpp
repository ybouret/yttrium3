
//! \file

#ifndef Y_RandomAccess_Included
#define Y_RandomAccess_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename T>
    class RandomAccess
    {
    public:
        Y_Args_Declare(T,Type);

        inline RandomAccess() noexcept  {}

        inline virtual ~RandomAccess() noexcept
        {
        }

        virtual void remove(const size_t indx) noexcept        = 0;
        virtual void demote(const size_t indx) noexcept        = 0;
        virtual void insert(const size_t indx, ParamType data) = 0;


    private:
        Y_Disable_Copy_And_Assign(RandomAccess);
    };

}

#endif // !Y_RandomAccess_Included

