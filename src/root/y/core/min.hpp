

//! \file

#ifndef Y_Core_Min_Included
#define Y_Core_Min_Included 1


namespace Yttrium
{

    template <typename T> inline
    T Min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    template <typename T> inline
    void InSituMin(T &ans, const T rhs)
    {
        if(rhs<ans) ans = rhs;
    }

    
}

#endif // !Y_Core_Min_Included

