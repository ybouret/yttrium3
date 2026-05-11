
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
            Y_XML_Element_Attr(xml,Tribes, Y_XML_Attr(cycle) << Y_XML_Attr(count) );
            for(const Tribe *tr=list.head;tr;tr=tr->next)
                tr->toXML(xml);
        }

        namespace
        {
            static inline
            bool FoundSameFamilyIn(const Tribe::List & target,
                                   const Tribe * const lhs) noexcept
            {
                for(const Tribe *rhs=target.head;rhs;rhs=rhs->next)
                {
                    if( lhs->family == rhs->family)
                    {
                        return true;
                    }
                }
                return false;
            }
        }


        void Tribes:: noMultiple() noexcept
        {
            Tribe::List target;
            while(list.size)
            {
                Tribe * const lhs = list.popHead();
                if( FoundSameFamilyIn(target,lhs) )
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


        void Tribes:: precompile(const RSet &zset) noexcept
        {
            if(zset->size()) {
                for(Tribe *tr=list.head;tr;tr=tr->next)
                    tr->demote(*zset);
            }
        }


        void Tribes:: DemoteForward(Tribe * curr, const size_t zr) noexcept
        {
            while(curr)
            {
                curr->demote(zr);
                curr=curr->next;
            }
        }

        void Tribes:: DemoteReverse(Tribe * curr, const size_t zr) noexcept
        {
            while(curr)
            {
                curr->demote(zr);
                curr=curr->prev;
            }

        }


        void Tribes:: DemoteForward(Tribe * curr, const RSet &hired, const size_t zr) noexcept
        {
            while(curr)
            {
                if(curr->hired.contains(hired) && curr->ready.contains(zr))
                {
                    curr->demote(zr);
                }
                curr = curr->next;
            }
        }

        void Tribes:: DemoteReverse(Tribe * curr, const RSet &hired, const size_t zr) noexcept
        {
            while(curr)
            {
                if(curr->hired.contains(hired) && curr->ready.contains(zr))
                {
                    curr->demote(zr);
                }
                curr = curr->prev;
            }
        }
    }
}
