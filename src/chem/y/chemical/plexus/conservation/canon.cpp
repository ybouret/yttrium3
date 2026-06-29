

#include "y/chemical/plexus/conservation/canon.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Canon:: ~Canon() noexcept
            {
            }

            Canon:: Canon(const Law &first) :
            Roll<Species>(),
            laws(),
            next(0),
            prev(0),
            lfmt()
            {
                laws.pushTail(first);
            }

            bool Canon:: accepts(const Law &law) const noexcept
            {
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    if( (**ln).linkedTo(law) ) return true;
                }
                return false;
            }

            void Canon:: compile()
            {
                free();
                Coerce(lfmt.width) = 0;
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    const Law &law = **ln;
                    lfmt.enroll(law);
                    for(const Actor *ac=law->head;ac;ac=ac->next)
                    {
                        inscribe(ac->sp);
                    }
                }
                Indexed::AuxLabel( Indexed::TopHSort( Coerce(list) ) );
            }

        }

    }

}
