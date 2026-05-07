//! \file

#ifndef Y_Associative_Container_Inluded
#define Y_Associative_Container_Inluded 1

#include "y/container.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class Associative : public Container
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);
        

        inline explicit Associative() noexcept : Container() {}
        inline virtual ~Associative() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Associative);
    };

}

#endif // !Y_Associative_Container_Inluded

