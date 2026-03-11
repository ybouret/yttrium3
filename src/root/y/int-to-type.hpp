

//! \file

#ifndef Y_IntToType_Included
#define Y_IntToType_Included 1


namespace Yttrium
{

    //! convert an integer to a type
    template <int N> struct IntToType
    {
        static const int Value = N; //!< original value
    };

}

#endif // !Y_IntToType_Included
