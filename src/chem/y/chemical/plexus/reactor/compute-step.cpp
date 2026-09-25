#include "y/chemical/plexus/reactor.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Reactor:: computeStep(XML::Log &xml)
        {

            const size_t nb = basis->size; assert(nb>0);
            Y_XML_Element_Attr(xml,ComputeStep, Y_XML_Attr(nb) );

            //__________________________________________________________________
            //
            //
            // fetch algebraic elements
            //
            //__________________________________________________________________
            Algebra     &alg = *resources->algebra;
            XMatrix &    J   = alg.J[nb];
            XMatrix &    dA  = alg.dA[nb];
            XMatrix &    nu  = alg.nu[nb];
            XMatrix &    nuT = alg.nuT[nb];
            XArray  &    xi  = alg.xi[nb];
            //__________________________________________________________________
            //
            //
            // prepare affinity jacobian, nu and rhs  (a.k.a xi)
            //
            //__________________________________________________________________
            dA.ld(MKL::Numeric<xreal_t>::ZERO);
            {
                size_t i=1;
                for(const ANode *an=basis->head;an;an=an->next,++i)
                {
                    const Assay      & assay = **an;
                    const Components & eq    = assay.eq;
                    eq.dAffinity(dA[i],Cini,SubLevel);
                    nu[i].load(cluster.allNu[  eq.indx[SubLevel] ] );
                    xi[i] = -assay.A0;
                }
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
            for(size_t i=nb;i>0;--i)
            {
                J[i][i] = xadd.dot(dA[i],nu[i]);
                for(size_t j=i-1;j>0;--j)
                    J[i][j] = J[j][i] = xadd.dot(dA[i],nu[j]);
            }
            Y_XMLog(xml,"J="  << J);

            //__________________________________________________________________
            //
            //
            // compute xi
            //
            //__________________________________________________________________
            if(!alg.lu.build(J))
            {
                Y_XMLog(xml, "[singular composition]");
                dC.ld(MKL::Numeric<xreal_t>::ZERO);
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

            return true;
        }

    }

}
