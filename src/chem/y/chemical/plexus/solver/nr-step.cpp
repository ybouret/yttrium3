#include "y/chemical/plexus/solver.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: NRStep(XML::Log &xml, const XReadable &C, const Level L)
        {
            //__________________________________________________________________
            //
            //
            // fetch algebraic elements
            //
            //__________________________________________________________________
            const size_t n   = ans.size();
            Algebra     &alg = *assets->algebra;
            XMatrix &    J   = alg.J[n];
            XMatrix &    dA  = alg.dA[n];
            XMatrix &    nu  = alg.nu[n];
            XMatrix &    nuT = alg.nuT[n];
            XArray  &    xi  = alg.xi[n];

            Y_XML_Element_Attr(xml,NewtonRaphson,Y_XML_Attr(n));

            //__________________________________________________________________
            //
            //
            // prepare affinity jacobian, nu and rhs  (a.k.a xi)
            //
            //__________________________________________________________________
            dA.ld(MKL::Numeric<xreal_t>::ZERO);
            for(size_t i=1;i<=n;++i)
            {
                Ansatz    & a    = ans[i];
                a.eq.dAffinity(dA[i],C,L);
                nu[i].load(cls.allNu[ a.eq.indx[SubLevel]] );
                xi[i] = -a.A0;
            }
            nuT.assignTranspose(nu);


            Y_XMLog(xml,"dA="  << dA);
            Y_XMLog(xml,"nu="  << nu);
            Y_XMLog(xml,"rhs=" << xi);

            //__________________________________________________________________
            //
            //
            // compute Jacobian dA*nu'
            //
            //__________________________________________________________________
            for(size_t i=n;i>0;--i)
            {
                J[i][i] = xadd.dot(dA[i],nu[i]);
                for(size_t j=i-1;j>0;--j)
                {
                    J[i][j] = J[j][i] = xadd.dot(dA[i],nu[j]);
                }
            }
            Y_XMLog(xml,"J="  << dA);

            //__________________________________________________________________
            //
            //
            // compute xi
            //
            //__________________________________________________________________
            if(!alg.lu.build(J))
            {
                Y_XMLog(xml, "[singular composition]");
                return false;
            }

            //__________________________________________________________________
            //
            //
            // compute dC
            //
            //__________________________________________________________________
            alg.lu.solve(J,xi);
            
            nuT.mul(dC,xi);
            Y_XMLog(xml, "xi=" << xi);
            Y_XMLog(xml, "dC=" << dC);

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
                const Species &sp = **sn;
                const size_t   j  = sp.indx[SubLevel];
                const xreal_t  cc = Cini[j]; assert(cc.mantissa>=0);
                const xreal_t  dc = dC[j];



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
            



            return false;
        }
    }
}
