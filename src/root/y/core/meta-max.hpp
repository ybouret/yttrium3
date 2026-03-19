
//! \file

#ifndef Y_Core_MetaMax_Included
#define Y_Core_MetaMax_Included 1


namespace Yttrium
{
    template <size_t A, size_t B>
    struct MetaMax
    {
        static const size_t Value = A<B ? B : A;
    };


}

#endif // !Y_Core_MetaMax_Included

