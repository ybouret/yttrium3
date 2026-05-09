
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

        void Tribe:: toXML(XML::Log &xml) const
        {
            Y_XML_Element_Attr(xml,Tribe,Y_XML_Attr(hired) << Y_XML_Attr(ready));
            family.toXML(xml);
        }

        void Tribe:: demoteNull(const RList &indx) noexcept
        {
            for(const RNode *node=indx->head;node;node=node->next)
            {
                const size_t  i = **node; if(hired->found(i)) continue;
                RNode * const z  = Coerce(ready).remove(i); assert(z);
                Coerce(hired).insert(z);
            }
        }


    }

}
