//! \file

#ifndef Y_Core_Max_Included
#define Y_Core_Max_Included 1


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //! inline maximum of two values
    /**
     \param a first value
     \param b second value
     \return a < b ? b : a;
     */
    //__________________________________________________________________________
    template <typename T> inline
    T Max(const T a, const T b)
    {
        return a < b ? b : a;
    }

    //__________________________________________________________________________
    //
    //! in-situ maximum update
    /**
     \param ans current maximum, updated if necessary
     \param rhs argument to test
     */
    //__________________________________________________________________________
    template <typename T> inline
    void InSituMax(T &ans, const T rhs)
    {
        if(ans<rhs) ans = rhs;
    }


}

#endif // !Y_Core_Max_Included

