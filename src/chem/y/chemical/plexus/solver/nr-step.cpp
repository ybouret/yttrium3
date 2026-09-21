#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: NRStep(XML::Log        & xml,
                             const xreal_t     F0,
                             const XReadable & C,
                             const Level       L)
        {
            Y_XML_Element(xml,NewtonRaphson);
            Y_XMLog(xml, "F0=" << F0.str());

            if(!computeStep(xml,C,L))
                return false;


            //__________________________________________________________________
            //
            //
            // check if need to cut
            //
            //__________________________________________________________________
            bool    cut = false;
            xreal_t fac = MKL::Numeric<xreal_t>::ONE;
            for(const SNode *sn=cls.slist->head;sn;sn=sn->next)
            {
                const Species & sp = **sn;
                const size_t    j  = sp.indx[SubLevel];
                const xreal_t   cc = Cini[j]; assert(cc.mantissa>=0);
                const xreal_t   dc = dC[j];



                if(xml.verbose)
                    cls.sfmt.print(xml(),"[",sp,"]")
                    << " : "  << std::setw(23) << cc.str()
                    << " + (" << std::setw(23) << dc.str() << ")" << std::endl;
                if(dc.mantissa<0)
                {
                    const xreal_t dd = -dc; assert(dd.mantissa>0);
                    if(dd>=cc)
                    {
                        cut = true;
                        InSituMin(fac,cc/dd);
                    }
                }
            }
            Y_XMLog(xml, "cut=" << cut << ", fac=" << fac);

            const size_t m = cls.M;
            if(cut)
            {
                for(size_t j=m;j>0;--j)
                    Cend[j] = Cini[j] + fac * dC[j];
            }
            else
            {
                for(size_t j=m;j>0;--j)
                    Cend[j] = Cini[j] + dC[j];
            }

            const xreal_t F1 = F(Cend,SubLevel);
            Y_XMLog(xml, "F1=" << F1.str());

            if(Trace)
            {
                OutputFile fp("nr-step.ycp");
                saveProfile(fp,TracePoints);
            }

            // TODO: study / optimize


            return false;
        }
    }
}
