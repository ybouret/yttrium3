
#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/output.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool     Reactor:: TracePro       = false;
        bool     Reactor:: TraceRun       = false;

        unsigned Reactor:: TracePoints = 200;

        const char * const Reactor:: StdProfileExt = "ycp";
        const char * const Reactor:: OptProfileExt = "yop";
        const real_t       Reactor:: DefaultSafety = 0.95;

        Reactor:: ~Reactor() noexcept
        {
        }

        Reactor:: Reactor(const Cluster &cl) :
        Object(),
        cluster(cl),
        N(cl.N),
        M(cl.M),
        n(cl.elist->size),
        F0(),
        Fs(),
        Cini(M),
        Cend(M),
        Ctry(M),
        dC(M),
        Ceq(n,M),
        basis(),
        assays(n),
        xmul(),
        xadd(),
        fadd(),
        last(false),
        expand(2.0),
        safety(DefaultSafety),
        resources( new Resources(N,M) ),
        next(0),
        prev(0),
        gpStd(),
        gpOpt()
        {

        }



        xreal_t Reactor:: ObjectiveFunction(const XReadable &C, const Level L)
        {
            fadd.ldz();
            for(size_t i=assays.size();i>0;--i)
            {
                const xreal_t AA = assays[i].affinity(C,L,xadd);
                const xreal_t A2 = AA*AA;
                fadd.add(A2);
            }
            return fadd().sqrt();
        }

        xreal_t Reactor:: operator()(const xreal_t u)
        {
            const xreal_t v = MKL::Numeric<xreal_t>::ONE - u;

            for(size_t j=M;j>0;--j)
            {
                xreal_t       cmin = Cini[j];
                xreal_t       cmax = Cend[j];
                const xreal_t c0   = cmin;
                const xreal_t c1   = cmax;
                if(cmin>cmax) Swap(cmin,cmax);
                Ctry[j] = Clamp(cmin,c0*v+c1*u,cmax);
            }

            return ObjectiveFunction(Ctry,SubLevel);
        }

        String Reactor:: MakeFileName(const String &id)
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


        void Reactor:: saveProfile(OutputStream &fp)
        {
            fp("0 %.15g\n", (double) ObjectiveFunction(Cini,SubLevel) );
            for(unsigned i=1;i<TracePoints;++i)
            {
                const real_t u = ((real_t)i) / TracePoints;
                fp("%.15g %.15g\n", u, (double) (*this)(u) );
            }
            fp("1 %.15g\n", (double) ObjectiveFunction(Cend,SubLevel) );
        }


        bool Reactor:: convergence(const XReadable &C0, const Level L0,
                                   const XReadable &C1, const Level L1) const noexcept
        {
            for(const SNode *sn = cluster.slist->head;sn;sn=sn->next)
            {
                const Species &sp = **sn;
                if( !MKL::AlmostEqual<xreal_t>::Are(sp(C0,L0),sp(C1,L1)) ) return false;
            }
            return true;
        }

    }

}
