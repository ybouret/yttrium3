
#include "y/chemical/plexus/conservation/canons.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Y_Proxy_Impl(Canons,list)

            Canons:: ~Canons() noexcept
            {
            }


            void Canons:: makeContent(XML::Log                & xml,
                                      const Core::ListOf<Law> & laws,
                                      const Assembly          & lfmt)
            {
                typedef Handy::BasicLightList<Canon> CList;

                for(const Law *node=laws.head;node;node=node->next)
                {
                    CList      clist;
                    const Law &law = *node;
                    for(Canon *canon=list.head;canon;canon=canon->next)
                        if(canon->accepts(law)) clist << *canon;

                    const size_t n = clist->size;
                    if(xml.verbose) lfmt.print(xml() << "[*] ",law,Justify::Center) <<" accepted by #" << n << std::endl;
                    switch(n)
                    {
                        case 0: list.pushTail( new Canon(law) ); continue;
                        case 1: (**(clist->head) ).laws << law;  continue;
                        default:
                            break;
                    }
                    assert(n>=2);
                    CList::NodeType * cnode  = clist->head;
                    Canon           & target = **cnode;
                    LList           & tgt    = target.laws;
                    for(cnode=cnode->next;cnode;cnode=cnode->next)
                    {
                        Canon &source = **cnode;
                        LList &src    = source.laws;
                        tgt->mergeTail(*src);
                        delete list.pop( &source );
                    }
                    tgt << law;
                }
            }


            void Canons:: postProcess(XML::Log &xml, const Topology &topo)
            {
                assert(list.size>0);
                const size_t count=list.size;
                Y_XML_Element_Attr(xml,Compilation, Y_XML_Attr(count) );
                for(Canon *node=list.head;node;node=node->next)
                {
                    Canon &canon    = *node;
                    canon.compile(xml,topo);
                }
            }

            Canons:: Canons(XML::Log                & xml,
                            const Core::ListOf<Law> & laws,
                            const Topology          & topo,
                            const Assembly          & lfmt) :
            list()
            {
                if(laws.size)
                {
                    Y_XML_Element_Attr(xml,BuildCanons,Y_XML_Attr(laws.size) );
                    makeContent(xml,laws,lfmt);
                    postProcess(xml,topo);
                }
            }
        }

    }

}
