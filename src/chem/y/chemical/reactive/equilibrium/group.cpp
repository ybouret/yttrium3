
#include "y/chemical/reactive/equilibrium/group.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        EGroup:: EGroup( Equilibrium &first ) :
        Object(),
        EList(),
        next(0),
        prev(0)
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
            Indexed::TopHSort(*this);
            Indexed::SubLabel(*this);
        }


        bool EGroup:: accepts(const Equilibrium &another) const noexcept
        {
            for(const ENode *en=(**this).head;en;en=en->next)
            {
                if( (**en).linkedTo(another) ) return true;
            }
            return false;
        }
    }

}
