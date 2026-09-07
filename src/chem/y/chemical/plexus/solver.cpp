#include "y/chemical/plexus/solver.hpp"
#include "y/core/hsort.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        bool Solver:: Trace = false;
        
        Solver:: Solver( const Cluster  &cluster) :
        cls(cluster),
        Ceq(cls.elist->size,cls.M),
        Cini(cls.M),
        Cend(cls.M),
        Ctry(cls.M),
        ans(cls.elist->size),
        xmul(),
        xadd(),
        Fadd(),
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


            // Initialize starting point
            Indexed::Transfer(Cini,SubLevel,C,L,cls.slist);
            const xreal_t F0 = F(C,L);
            Y_XMLog(xml, "F0 = " << F0.str());

            // initialize Cini at starting point
            if(Trace)
            {
                OutputFile::Overwrite("solver.gp");
            }

            for(size_t i=1;i<=n;++i)
            {
                const Ansatz & a  = ans[i];
                optimizing(xml,a,F0,i);

            }


            //XMatrix &J = jac[n]; std::cerr << "J=" << J << std::endl;
        }

    }

}

#include "y/core/clamp.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        String Solver:: MakeFileName(const String &id)
        {
            String s;
            for(size_t i=1;i<=id.size();++i)
            {
                const char c = id[i];
                if( isalnum(c) || c == '-' || c == '+' )
                {
                    s << c;
                }
                else
                    s << '_';
            }
            return s;
        }

        namespace
        {
            static inline
            void savePoint(OutputStream &fp, Solver &solver, const xreal_t u)
            {
                const xreal_t f = solver.F(u);
                fp << u.str() << ' ' << f.str() << '\n';
            }

        }
        
        void Solver:: saveProfile(OutputStream & fp,
                                  const unsigned np)
        {

            savePoint(fp,*this,0);
            const xreal_t den(np);
            for(unsigned i=1;i<np;++i)
            {
                const xreal_t u = xreal_t(i) / den;
                savePoint(fp,*this,u);
            }
            savePoint(fp,*this,1);
        }



        xreal_t Solver:: F(const XReadable &C, const Level L)
        {
            Fadd.ldz();
            for(size_t i=ans.size();i>0;--i)
            {
                const xreal_t A  = ans[i].affinity(xadd,C,L);
                const xreal_t A2 = A*A;
                Fadd << A2;
            }
            return Fadd().sqrt();
        }

        xreal_t Solver:: F(const xreal_t u)
        {
            const xreal_t one(1);
            const xreal_t v = one - u;
            for(size_t j=cls.M;j>0;--j)
            {
                xreal_t cmin = Cini[j]; const xreal_t c0 = cmin;
                xreal_t cmax = Cend[j]; const xreal_t c1 = cmax;
                if(cmax<cmin) Swap(cmin,cmax);
                Ctry[j] = Clamp(cmin,c0*v+c1*u,cmax);
            }
            return F(Ctry,SubLevel);
        }


    }
}
