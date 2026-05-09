
#include "y/coven/tribes.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Tribes:: ~Tribes() noexcept
        {
        }

        
        const Tribe::List & Tribes:: locus() const noexcept
        {
            return list;
        }

        void Tribes:: toXML(XML::Log &xml) const
        {
            const size_t count = list.size;
            Y_XML_Element_Attr(xml,Tribes, Y_XML_Attr(count) << Y_XML_Attr(hired) << Y_XML_Attr(ready) );
            for(const Tribe *tr=list.head;tr;tr=tr->next)
            {
                tr->toXML(xml);
            }
        }

    }
}
