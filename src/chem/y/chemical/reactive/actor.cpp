
#include "y/chemical/reactive/actor.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Actor:: ~Actor() noexcept
        {
        }

        Actor:: Actor(const unsigned & _nu,
                      const Species  & _sp,
                      const Acting     _id) :
        Object(),
        Entity(),
        nu(_nu),
        sp(_sp),
        next(0),
        prev(0)
        {
            assert(nu>0);
            String alias;
            if(nu>1)
            {
                alias = Formatted::Get("%u",nu);
            }

            switch(_id)
            {
                case AsSpec: alias += sp.name; break;
                case AsConc: alias += '[' + sp.name + ']'; break;
            }

            alias.xch( Coerce(name) );
        }
    }

}

