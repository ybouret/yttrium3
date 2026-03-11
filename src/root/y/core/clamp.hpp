
//! \file

#ifndef Y_Core_Clamp_Included
#define Y_Core_Clamp_Included 1


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //! inline clamping between two values
    /**
     \param lower lower bound
     \param value value to test
     \param upper upper bound
     \return clamped value
     */
    //__________________________________________________________________________
    template <typename T> inline
    T Clamp(const T lower, const T value, const T upper)
    {
        if(value<=lower)
            return lower;
        else
        {
            if(upper<=value)
                return upper;
            else
                return value;
        }
    }
}

#endif // !Y_Core_Clamp_Included
