
//! \file

#ifndef Y_Object_Drifter_Included
#define Y_Object_Drifter_Included 1

#include "y/object.hpp"


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
    class Object::Drifter
    {
    public:
        class Hideout;

        explicit Drifter() noexcept;
        virtual ~Drifter() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Drifter);
    };
}

#endif // !Y_Object_Drifter_Included

