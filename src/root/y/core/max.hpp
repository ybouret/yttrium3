


//! \file

#ifndef Y_Core_Max_Included
#define Y_Core_Max_Included 1


namespace Yttrium
{

    template <typename T> inline
    T Max(const T a, const T b)
    {
        return a < b ? b : a;
    }

    template <typename T> inline
    void InSituMax(T &ans, const T rhs)
    {
        if(ans<rhs) ans = rhs;
    }


}

#endif // !Y_Core_Max_Included

