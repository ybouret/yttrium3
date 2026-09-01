
#include "y/chemical/plexus/solver.hpp"
#include "y/core/hsort.hpp"
#include "y/ascii/plural.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        size_t Solver:: buildBasis(XML::Log        & xml,
                                   XWritable       & C,
                                   const Level       L,
                                   const XReadable & K)
        {
            size_t       n = regularize(xml,C,L,K);
            const size_t N = cls.N;

            Y_XML_Element(xml,BuildBasis);
            Y_XMLog(xml, "-- initializing individual affinities");

            //------------------------------------------------------------------
            //
            // computing individual affinities
            //
            //------------------------------------------------------------------
            for(size_t i=n;i>0;--i)
            {
                Ansatz  &a     = ans[i]; assert(a.am.st==Running);
                Coerce(a.A0)  = a.affinity(xadd,C,L);
            }


            //------------------------------------------------------------------
            //
            // prepare selection
            //
            //------------------------------------------------------------------
            Core::HSort::Make( &ans[1], n, Ansatz::DecreasingAA );


            if(xml.verbose)
            {
                for(size_t i=1;i<=n;++i)
                {
                    const Ansatz  &a  = ans[i]; assert(a.am.st==Running);
                    Y_XMLog(xml, " @ xi = " << std::setw(22) << a.am.xi.str()
                            <<   " | A0 = " << std::setw(22) << a.A0.str()
                            <<   " | " << a.eq);
                }
            }

            //------------------------------------------------------------------
            //
            // selecting
            //
            //------------------------------------------------------------------
            Y_XMLog(xml, "-- selecting at most " << N << " equilibri" << ASCII::Plural::uma(N) << " out of " << ans.size() );
            finder->free();
            for(size_t i=1;i<=n;++i)
            {
                const Ansatz      &a  = ans[i]; assert(a.am.st==Running);
                const Equilibrium &eq = a.eq;
                const IRow        &nu = cls.allNu[  eq.indx[SubLevel] ];
                if(finder->accepts(nu))
                {
                    Y_XMLog(xml, "[+] " << eq.name);
                    if(finder->size>=N)
                    {
                        Y_XMLog(xml, "-- found FULL basis");
                        break;
                    }
                }
                else
                {
                    Y_XMLog(xml, "[-] " << eq.name);
                    ans.remove(i);
                    --n;
                }
            }


            //------------------------------------------------------------------
            //
            // cleanup
            //
            //------------------------------------------------------------------
            n = finder->size;
            if(n<N) Y_XMLog(xml, "-- found PARTIAL basis");
            while(ans.size()>n)
                ans.popTail();
            assert(ans.size() == n);
            return n;
        }

    }

}

