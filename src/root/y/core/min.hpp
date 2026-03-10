

//! \file

#ifndef Y_Core_Min_Included
#define Y_Core_Min_Included 1


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //! inline minimum of two values
    /**
     \param a first value
     \param b second value
     \return a < b ? a : b;
     */
    //__________________________________________________________________________
    template <typename T> inline
    T Min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    //__________________________________________________________________________
    //
    //! in-situ minimum update
    /**
     \param ans current minimum, updated if necessary
     \param rhs argument to test
     */
    //__________________________________________________________________________
    template <typename T> inline
    void InSituMin(T &ans, const T rhs)
    {
        if(rhs<ans) ans = rhs;
    }

    
}

#endif // !Y_Core_Min_Included

