
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

        static inline bool FoundIn(const Tribe::List &target, const Tribe * const lhs) noexcept
        {
            for(const Tribe *rhs=target.head;rhs;rhs=rhs->next)
            {
                if( lhs->hired == rhs->hired )
                {
                    assert(lhs->ready == rhs->ready);
                    return true;
                }
            }
            return false;
        }


        void Tribes:: noMultiple() noexcept
        {
            Tribe::List target;
            while(list.size)
            {
                Tribe * const lhs = list.popHead();
                if( FoundIn(target,lhs) )
                {
                    delete lhs;
                }
                else
                {
                    target.pushTail(lhs);
                }
            }
            list.swapForList(target);
        }

    }
}
