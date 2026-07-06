
#include "y/chemical/plexus/conservation/adjudicator.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            

            Adjudicator:: ~Adjudicator() noexcept
            {
            }

            Adjudicator:: Adjudicator(const Canon &source) :
            canon(source),
            blist(),
            xadd(),
            n(canon.laws->size),
            m(canon.species->list->size),
            wksp(n,m)
            {
                blist.cache->cache(n);
            }

            namespace
            {
                static inline SignType IncreasinglyBroken(const Broken &lhs, const Broken &rhs) noexcept
                {
                    return Sign::Of(lhs.bad,rhs.bad);
                }

            }
            void Adjudicator:: judge(XML::Log  & xml,
                                     XWritable & C,
                                     const Level L)
            {
                Y_XML_Element_Attr(xml,Trail, Y_XML_Attr(n));

                Y_XMLog(xml,"-- Collect");
                Core::Display(std::cerr << "C=",&C[1], C.size(), xreal_t::ToString) << std::endl;
                blist.free();
                for(const LNode *ln=canon.laws->head;ln;ln=ln->next)
                {
                    const Law    &  law = **ln;
                    const xreal_t   bad = law.excess(C,L,xadd); if(bad.mantissa<=0) continue;
                    XWritable     & prj = wksp[blist->size+1];
                    const Broken    brk(law,bad,law.project(prj,AuxLevel,C,L,xadd));
                    Y_XMLog(xml,"[-] " << brk);
                    blist << brk;
                }


                while(blist->size)
                {
                    Y_XMLog(xml,"-- Inflate");
                    // sorting
                    blist->sortBy(IncreasinglyBroken);
                    Broken &broken = **blist->head;
                    Y_XMLog(xml, "[*] " << broken);
                    broken.law.transfer(C,L,broken.prj,AuxLevel);
                    Core::Display(std::cerr << "C=",&C[1], C.size(), xreal_t::ToString) << std::endl;

                    break;
                }

            }

        }
    }
}


