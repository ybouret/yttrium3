
#include "y/chemical/plexus/conservation/law.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Law:: Law(const size_t i) noexcept :
            Actors(AsConc),
            irow(i),
            next(0),
            prev(0)
            {
            }

            Law:: ~Law() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Law &law)
            {
                return os << "d_(" << law.name << ")";
            }

            xreal_t Law:: excess(const XReadable &C, const Level L, XAdd &xadd) const
            {
                xadd.ldz();
                for(const Actor *ac=(**this).head;ac;ac=ac->next)
                {
                    const xreal_t acc = ac->xn * ac->sp(C,L);
                    xadd << acc;
                }
                return xadd();
            }


        }

    }

}

