
//! \file

#ifndef Y_LightObject_Included
#define Y_LightObject_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //!  
    //
    //
    //__________________________________________________________________________
    class LightObject
    {
    public:
        class Factory;

        explicit LightObject() noexcept;
        virtual ~LightObject() noexcept;

    private:
        Y_Disable_Copy_And_Assign(LightObject);
    };
}

#endif // !Y_LightObject_Included

