
//! \file

#ifndef Y_Associative_SuffixProto_Inluded
#define Y_Associative_SuffixProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/tree.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class SuffixProto
    {
    public:
        

        inline virtual ~SuffixProto() noexcept {}

    private:
        Y_Disable_Assign(SuffixProto);
    };

}

#endif // !Y_Associative_SuffixProto_Inluded

