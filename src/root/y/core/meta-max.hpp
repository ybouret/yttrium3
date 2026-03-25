
//! \file

#ifndef Y_Core_MetaMax_Included
#define Y_Core_MetaMax_Included 1


namespace Yttrium
{
    //! choice of maximum value
    template <size_t A, size_t B>
    struct MetaMax
    {
        static const size_t Value = A<B ? B : A; //!< result
    };

    //! choice of maximum value
    template <size_t A, size_t B, size_t C>
    struct MetaMaxOfTriplet
    {
        static const size_t Value = MetaMax<MetaMax<A,B>::Value, C>::Value; //!< result
    };



}

#endif // !Y_Core_MetaMax_Included

