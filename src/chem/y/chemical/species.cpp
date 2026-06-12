

#include "y/chemical/species.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Species:: ~Species() noexcept
        {
        }

        Species:: Species(const Formula &f, const size_t i) :
        CountedObject(),
        Formula(f),
        Indexed(i),
        z(0)
        {
            String _ = makeName(& Coerce(z) );
            Coerce(name).xch(_);
        }



    }

}


