
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
        Ceq(n,M),
        basis(),
        assays(n),
        xmul(),
        xadd(),
        fadd(),
        resources( new Resources(N,M) )
        {

        }

        Reactor::Outcome Reactor:: run(XML::Log &xml, XWritable &C, const Level L, const XReadable &K)
        {
            Y_XML_Element(xml,ReactorRun);

            // initialize for consistency
            F0.ldz();
            basis.free();

            // build RUNNING assays, tweaking C
            const size_t na = buildAssays(xml,C,L,K);
            Y_XMLog(xml,"#assay = " << na);
            if(na<=0)
            {
                return Achieved;
            }

            // initialize from assays
            Indexed::Transfer(Cini,SubLevel,C,L,cluster.slist);
            F0 = ObjectiveFunction(Cini,SubLevel);
            Y_XMLog(xml,"F0 = " << F0.str());

            // study and optimize assays
            const size_t        ok     = studyAssays(xml);
            const Assay * const best1D = (ok<=0) ? 0 : & assays[1];
            if(best1D)
            {
                Y_XMLog(xml, "[best1D] " << best1D->F1.str() << " @" << best1D->eq.name);
            }
            else
            {
                Y_XMLog(xml, "[best1D] NONE");
            }

            // create local basis
            createBasis(xml);

            
            return Spurious;
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
                xreal_t cmin = Cini[j];
                xreal_t cmax = Cend[j];
                const xreal_t c0 = cmin;
                const xreal_t c1 = cmax;
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
