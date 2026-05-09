
#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Survey:: Survey() noexcept :
        Proxy<const Vectors>(),
        list(),
        sampling(0)
        {
        }

        Survey:: ~Survey() noexcept
        {
        }

        const Vectors & Survey:: locus() const noexcept { return list; }

        Survey & Survey:: operator<< (const Vector &v)
        {
            if(v.ncof<=0) return *this;
            if(!takes(v)) return *this;
            Vector * const node = list.pushTail( new Vector(v) );
            while(node->prev && Vector::Compare(*(node->prev),*node) == Positive )
                list.towardsHead(node);
            ++Coerce(sampling);
            return *this;
        }

        void Survey:: release() noexcept
        {
            list.release();
            Coerce(sampling) = 0;
        }

    }

}
