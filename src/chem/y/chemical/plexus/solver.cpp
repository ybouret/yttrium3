#include "y/chemical/plexus/solver.hpp"
#include "y/core/hsort.hpp"

namespace Yttrium
{
    namespace Chemical
    {



        Solver:: Solver( const Cluster  &cluster) :
        cls(cluster),
        Ceq(cls.elist->size,cls.M),
        ans(cls.elist->size),
        xmul(),
        xadd(),
        jac(cls.N),
        finder( new Coven::Finder(cls.M) )
        {
            for(size_t i=1;i<=cls.N;++i)
            {
                jac.append(i,i);
                assert(jac[i].isSquare());
            }

        }



        Solver:: ~Solver() noexcept
        {
        }


        void Solver:: run(XML::Log        & xml,
                          XWritable       & C,
                          const Level       L,
                          const XReadable & K)
        {
            const size_t count = cls.elist->size;
            Y_XML_Element_Attr(xml,SolverRun, Y_XML_Attr(count) );
            const size_t n = buildBasis(xml,C,L,K);
            Y_XMLog(xml, "dof = " << n);
            
        }


    }
}
