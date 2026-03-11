
//! \file

#ifndef Y_TypeToType_Included
#define Y_TypeToType_Included 1


namespace Yttrium
{
    //! type indicator
    template <typename T>
    struct TypeToType
    {
        typedef T Type; //!< original value
    };

}

#endif // !Y_TypeToType_Included
