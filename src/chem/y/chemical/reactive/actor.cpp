
#include "y/chemical/reactive/actor.hpp"
#include "y/string/format.hpp"
#include "y/core/max.hpp"

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
        xn(nu),
        zero(),
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
                case AsSpec: alias += ' ' + sp.name; break;
                case AsConc: alias += '[' + sp.name + ']'; break;
            }

            alias.xch( Coerce(name) );
        }


        void Actor:: massAction(XMul &X, const XReadable &C, const Level L) const
        {
            const xreal_t c = sp(C,L); assert(c>=zero);
            X.power(c,nu);
        }

        void Actor:: massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            xreal_t c = sp(C,L); assert(c>=zero);
            InSituMax(c += xn * xi,zero);
            X.power(c,nu);
        }

        xreal_t Actor:: extent(const XReadable &C, const Level L) const noexcept
        {
            assert(sp(C,L)>=zero);
            return sp(C,L)/xn;
        }

        void Actor:: safeMove(XWritable &C, const Level L, const xreal_t xi) const noexcept
        {
            xreal_t &c = sp(C,L); assert(c>=zero);
            InSituMax(c += xn * xi,zero);
        }


    }

}

