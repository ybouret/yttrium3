
#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool     Reactor:: Trace       = false;
        unsigned Reactor:: TracePoints = 200;

        const char * const Reactor:: StdProfileExt = "ycp";
        const char * const Reactor:: OptProfileExt = "yop";


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
        resources( new Resources(N,M) ),
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

    }

}
