

//! \file

#ifndef Y_IntToType_Included
#define Y_IntToType_Included 1


namespace Yttrium
{

    template <int N>
    struct IntToType
    {
        static const int Value = N;
    };

}

#endif // !Y_IntToType_Included
