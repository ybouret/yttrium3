

#include "y/chemical/species.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Species:: ~Species() noexcept
        {
        }

        Species:: Species(const Formula &f) :
        CountedObject(),
        Formula(f),
        z(0),
        name( makeName( &Coerce(z) ) )
        {
        }
        
    }

}


