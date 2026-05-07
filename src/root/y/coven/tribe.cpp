
#include "y/coven/tribe.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Tribe:: ~Tribe() noexcept
        {
        }

        void Tribe:: setup(const size_t ir, const size_t nr)
        {
            assert(ir>=1);
            assert(ir<=nr);

            for(size_t i=1;i<ir;++i)     Coerce(ready) << i;
            for(size_t i=ir+1;i<=nr;++i) Coerce(ready) << i;
            Coerce(hired) << ir;
        }
    }

}
