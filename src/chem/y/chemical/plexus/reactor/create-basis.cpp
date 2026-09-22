#include "y/chemical/plexus/reactor.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Reactor:: createBasis(XML::Log &xml)
        {
            const size_t na = assays.size(); assert(na>0);
            Y_XML_Element_Attr(xml,CreateBasis,Y_XML_Attr(na) << Y_XML_Attr(N) );

            assert(0==basis->size);
            Coven::Finder &finder = *resources->finder;
            finder.free();
            for(size_t i=1;i<=na;++i)
            {
                const Assay       &assay = assays[i];
                const Components  &eq    = assay.eq;
                const IRow        &nu    = cluster.allNu[ eq.indx[SubLevel] ];
                if( finder.accepts(nu) )
                {
                    Y_XMLog(xml, "[+] " << eq.name);
                    basis << dynamic_cast<Equilibrium&>(Coerce(assay.eq));
                    if(finder.size>=N)
                        break;
                }
                else
                {
                    Y_XMLog(xml, "[-] " << eq.name);
                }
            }
            Y_XMLog(xml," | ");
            Y_XMLog(xml,"[*] basis is done with dim=" << basis->size);



        }
    }

}


