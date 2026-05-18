

//! \file

#ifndef Y_Associative_Catalog_Inluded
#define Y_Associative_Catalog_Inluded 1

#include "y/container/associative.hpp"

namespace Yttrium
{
    template <typename KEY, typename T>
    class Catalog : public Associative<KEY,T>
    {
    public:
        Y_Args_Declare(KEY,Key);
        Y_Args_Declare(T,Type);

        inline explicit Catalog() noexcept : Associative<KEY,T>() {}
        inline virtual ~Catalog() noexcept {}

        virtual bool insert(ParamKey, ParamType) = 0;

    private:
        Y_Disable_Copy_And_Assign(Catalog);
    };

}

#endif // !Y_Associative_Catalog_Inluded

