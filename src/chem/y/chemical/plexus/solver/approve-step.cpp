
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: approveStep(XML::Log        & xml)
        {
            Y_XML_Element(xml,ApproveStep);
            assert(cls.M == cls.slist->size);
            
            bool    mustCut = false;
            xreal_t xfactor = MKL::Numeric<xreal_t>::ONE;
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
                        mustCut = true;
                        InSituMin(xfactor,cc/dd);
                    }
                }
            }

            const size_t m = cls.M;
            if(mustCut)
            {
                Y_XMLog(xml, "Must Cut @" << xfactor.str());
                for(size_t j=m;j>0;--j)
                    Cend[j] = Cini[j] + xfactor * dC[j];
            }
            else
            {
                for(size_t j=m;j>0;--j)
                    Cend[j] = Cini[j] + dC[j];
            }

        }

    }

}

