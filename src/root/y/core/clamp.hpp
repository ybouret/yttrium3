
//! \file

#ifndef Y_Core_Clamp_Included
#define Y_Core_Clamp_Included 1


namespace Yttrium
{
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
