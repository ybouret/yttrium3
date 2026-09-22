#include "y/chemical/plexus/solver.hpp"
#include "y/core/hsort.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        bool         Solver:: Trace        = false;
        unsigned     Solver:: TracePoints  = 1000;
        const real_t Solver:: DefaultSafety = 0.95;

        Solver:: Solver( const Cluster  &cluster) :
        cls(cluster),
        Ceq(cls.elist->size,cls.M),
        Cini(cls.M),
        Cend(cls.M),
        Ctry(cls.M),
        dC(cls.M),
        Fg(),
        ans(cls.elist->size),
        blk(),
        xmul(),
        xadd(),
        Fadd(),
        expand( 2.0 ),
        safety( DefaultSafety ),
        assets( new Assets(cls.N,cls.M) ),
        next(0),
        prev(0),
        trace(),
        tropt(),
        runfn( Formatted::Get("solver%s.dat", Decimal(cls.gvid).c_str() ) )
        {
        }


        Solver:: ~Solver() noexcept
        {
        }


        const char * const Solver:: StdProfileExt = "ycp";
        const char * const Solver:: OptProfileExt = "yop";
        const char * const Solver:: AnyProfileExt = "y[c|o]p";


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
                const xreal_t f = solver(u);
                fp << u.str() << ' ' << f.str() << '\n';
            }

        }
        
        void Solver:: saveProfile(OutputStream & fp,
                                  const unsigned np)
        {

            savePoint(fp,*this,0.0);
            const xreal_t den(np);
            for(unsigned i=1;i<np;++i)
            {
                const xreal_t u = xreal_t(i) / den;
                savePoint(fp,*this,u);
            }
            savePoint(fp,*this,1.0);
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

        xreal_t Solver:: operator()(const xreal_t u)
        {
            const xreal_t one(1);
            const xreal_t v = one - u;
            for(size_t j=cls.M;j>0;--j)
            {
                xreal_t       cmin = Cini[j]; assert(cmin.mantissa>=0);
                xreal_t       cmax = Cend[j]; assert(cmax.mantissa>=0);
                const xreal_t c0   = cmin;
                const xreal_t c1   = cmax;

                if(cmax<cmin) Swap(cmin,cmax);
                assert(cmin<=cmax);
                Ctry[j] = Clamp(cmin,c0*v+c1*u,cmax);
            }

            
            return F(Ctry,SubLevel);
        }


    }
}
