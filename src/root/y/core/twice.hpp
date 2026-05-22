
//! \file

#ifndef Y_Core_Twice_Included
#define Y_Core_Twice_Included 1


namespace Yttrium
{
    //! \param a \return a+a
    template <typename T>
    inline T Twice(T a)
    {
        return a+a;
    }
}

#endif // !Y_Core_Twice_Included
