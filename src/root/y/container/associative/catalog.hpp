

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
        inline explicit Catalog() noexcept : Associative<KEY,T>() {}
        inline virtual ~Catalog() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Catalog);
    };

}

#endif // !Y_Associative_Catalog_Inluded

