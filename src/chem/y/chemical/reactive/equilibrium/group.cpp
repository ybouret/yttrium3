
#include "y/chemical/reactive/equilibrium/group.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        EGroup:: EGroup( Equilibrium &first ) : Object(), EList()
        {
            (*this) << first;
        }


        EGroup:: ~EGroup() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const EGroup &g)
        {
            os << '[';
            const ENode *en = g->head;
            if(en)
            {
                os << (**en).name;
                for(en=en->next;en;en=en->next) os << ',' << (**en).name;
            }
            return os << ']';
        }

        void EGroup:: finalize() noexcept
        {
            (**this).sortBy( Indexed::TopLevelCompare );
            Indexed::SubLabel(*this);
        }

    }

}
