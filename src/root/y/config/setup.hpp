
//! \file

#ifndef Y_Config_Setup_Included
#define Y_Config_Setup_Included 1

#include "y/config/setup.h"


#define Y_Disable_Copy(CLASS)   private: CLASS(const CLASS&)              //!< disable copy constructor
#define Y_Disable_Assign(CLASS) private: CLASS & operator=(const CLASS &) //!< disable assign operator

//! disable both copy and assign for a given CLASS
#define Y_Disable_Copy_And_Assign(CLASS) \
/**/    Y_Disable_Copy(CLASS);           \
/**/    Y_Disable_Assign(CLASS)

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //! coerce constant to mutable object
    /**
     \param obj const object
     \return mutable obj
     */
    //__________________________________________________________________________
    template <typename T> inline
    T & Coerce(const T &obj) noexcept { return (T&)obj; }

    namespace Core
    {
        extern const char * const Unknown; //!< "Unknown"
        extern const char * const Success; //!< "Success"
        extern const char * const Failure; //!< "Failure"
    };

}

//! helper to return named case
#define Y_Return_Named_Case(NAME) case NAME: return #NAME


#endif // !Y_Config_Setup_Included

