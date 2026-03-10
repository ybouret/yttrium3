//! \file

#ifndef Y_Hide_Included
#define Y_Hide_Included 1


namespace Yttrium
{

    struct Hide
    {
        static void *       Address(void * const)       noexcept;
        static const void * Address(const void * const) noexcept;
    };

}

#endif // !Y_Hide_Included
