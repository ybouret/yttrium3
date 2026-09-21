
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/tao/1.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: approveStep(XML::Log        & xml)
        {
            Y_XML_Element(xml,ApproveStep);
            assert(cls.M == cls.slist->size);
            xreal_t xfactor = MKL::Numeric<xreal_t>::ZERO;

            // scan species-wise step
            {
                bool mustCut = false;
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
                        assert(cc.mantissa>0);
                        const xreal_t dd = -dc; assert(dd.mantissa>0);
                        const xreal_t fac = cc/dd;
                        if(!mustCut)
                        {
                            mustCut = true;
                            xfactor = fac;
                        }
                        else
                        {
                            InSituMin(xfactor,fac);
                        }

                    }
                }

                if(mustCut)
                {

                    Y_XMLog(xml, "-- must cut @" << xfactor);
                    xfactor = Min(expand,xfactor*=safety);
                    Y_XMLog(xml, "-- will cut @" << xfactor);
                }
                else
                {
                    xfactor = MKL::Numeric<xreal_t>::ONE;
                    Y_XMLog(xml, "-- take full step");
                }
            }

            const size_t m = cls.M;

            {
            COMPUTE_CNEW:
                for(size_t j=m;j>0;--j)
                {
                    const xreal_t c0 = Cini[j];
                    const xreal_t c1 = c0+xfactor * dC[j];
                    if(c0.mantissa>0&&c1.mantissa<=0) {
                        Y_XMLog(xml, "-- numeric safety!");
                        xfactor *= safety;
                        goto COMPUTE_CNEW;
                    }
                    Cend[j] = c1;
                }
            }

            if(xml.verbose)
            {
                for(const SNode *sn=cls.slist->head;sn;sn=sn->next)
                {
                    const Species & sp = **sn;
                    const size_t    j  = sp.indx[SubLevel];
                    cls.sfmt.print(xml(),"[",sp,"]") << " = " << std::setw(23) << Cend[j].str() << std::endl;
                }
            }
            



        }

    }

}

