
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

            Canons:: Canons(XML::Log                & xml,
                            const Core::ListOf<Law> & laws,
                            const Assembly          & lfmt) :
            list()
            {
                typedef Handy::BasicLightList<Canon> CList;
                if(laws.size)
                {
                    Y_XML_Element_Attr(xml,BuildCanons,Y_XML_Attr(laws.size) );

                    //----------------------------------------------------------
                    //
                    //
                    // loop over given laws and dispatch
                    //
                    //
                    //----------------------------------------------------------
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
                    }

                    // compile each canon
                    assert(list.size>0);
                    const size_t count=list.size;
                    Y_XML_Element_Attr(xml,Compilation, Y_XML_Attr(count) );
                    for(Canon *node=list.head;node;node=node->next)
                    {
                        Canon       &canon    = *node;
                        const size_t cardinal = canon.laws->size;
                        Y_XML_Element_Attr(xml,CompileCanon, Y_XML_Attr(cardinal) );
                        canon.compile();
                        if(xml.verbose)
                        {
                            for(const LNode *ln=canon.laws->head;ln;ln=ln->next)
                            {
                                const Law &law = **ln;
                                canon.lfmt.print(xml() << "[+] d_( ",law,Justify::Center) << " )=0" << std::endl;
                            }
                        }
                        Y_XMLog(xml, "[@] " << canon.species->list);
                        //Y_XMLog(xml, "    Gamma = " << canon.Gamma);
                        //Y_XMLog(xml, "    rg    = " << canon.rg);
                    }
                }
            }
        }

    }

}
