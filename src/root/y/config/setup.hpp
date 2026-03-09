
//! \file

#ifndef Y_Config_Setup_Included
#define Y_Config_Setup_Included 1

#define Y_Disable_Copy(CLASS)   private: CLASS(const CLASS&)
#define Y_Disable_Assign(CLASS) private: CLASS & operator=(const CLASS &)

#define Y_Disable_Copy_And_Assign(CLASS) \
/**/    Y_Disable_Copy(CLASS); \
/**/    Y_Disable_Assign(CLASS)

namespace Yttrium
{
    template <typename T> inline
    T & Coerce(const T &obj) noexcept { return (T&)obj; }
}

#endif // !Y_Config_Setup_Included

