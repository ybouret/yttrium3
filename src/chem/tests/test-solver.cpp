

#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

#include "y/chemical/plexus/clusters.hpp"
#include "y/chemical/reactive/equilibrium/aftermath.hpp"

#include "y/container/cxx/array.hpp"
#include "y/string/env/convert.hpp"
#include "y/random/park-miller.hpp"

#include "y/mkl/algebra/xgj.hpp"
#include "y/string/format.hpp"

#include "y/vfs/local/fs.hpp"
#include "y/jive/vfs.hpp"

#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/container/cxx/series.hpp"
#include "y/chemical/type/concentration.hpp"
#include "y/core/hsort.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Ansatz
        {
        public:
            typedef CxxSeries<Ansatz> Series;

            const Equilibrium & eq;
            const xreal_t       eK;
            const Aftermath     am;
            const XReadable &   cc;

            Ansatz(const Equilibrium & _eq,
                   const xreal_t     & _eK,
                   const Aftermath   & _am,
                   const XReadable   & _cc) noexcept :
            eq(_eq),
            eK(_eK),
            am(_am),
            cc(_cc)
            {
            }

            Ansatz(const Ansatz &_) noexcept :
            eq(_.eq),
            eK(_.eK),
            am(_.am),
            cc(_.cc)
            {
            }


            ~Ansatz() noexcept {}

        private:
            Y_Disable_Assign(Ansatz);
        };

        class Solver
        {
        public:

            explicit Solver(const Cluster &cluster);
            virtual ~Solver() noexcept;

            void run(XML::Log        & xml,
                     XWritable       & C,
                     const Level       L,
                     const XReadable & K);

            const Cluster &cls;
            XMatrix        Ceq;
            Ansatz::Series ans;
            XMul           xmul;
            XAdd           xadd;

        private:
            Y_Disable_Copy_And_Assign(Solver);
        };

        Solver:: Solver( const Cluster  &cluster) :
        cls(cluster),
        Ceq(cls.elist->size,cls.M),
        ans(cls.elist->size)
        {
            
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

            {
                bool emergency = false;
                ans.free();
                for(const ENode *en=cls.elist->head;en;en=en->next)
                {
                    XWritable         & cc =  Indexed::Transfer(Ceq[ans.size()+1],SubLevel,C,L,cls.slist);
                    const Equilibrium & eq = **en;
                    const xreal_t       eK = eq(K,TopLevel);
                    const Aftermath     am = Aftermath::Compute(xml,cc,SubLevel,C,L,eq,eK,xmul,xadd);
                    switch(am.st)
                    {
                        case Blocked: continue;
                        case Running:
                            if(!emergency) ans.append(eq,eK,am,cc);
                            continue;
                        case Crucial:
                            emergency = true;
                            ans.append(eq,eK,am,cc);
                            continue;
                    }
                }

                if(emergency)
                {
                    Y_XML_Element(xml,Emergency);
                    for(size_t i=ans.size();i>0;--i)
                    {
                        Ansatz &a = ans[i];
                        if( a.am.st == Running)
                        {
                            Y_XMLog(xml, "[-] " << a.eq.name);
                            ans.demote(i);
                            ans.popTail();
                        }
                        else
                        {
                            assert( Crucial == a.am.st );
                            //Y_XMLog(xml, "[+] " << a.eq.name);
                        }
                    }

                    const size_t n = ans.size(); assert(n>=1);
                    for(size_t i=1;i<=n;++i)
                    {
                        const Ansatz &a = ans[i];
                        Y_XMLog(xml, "@xi = " << std::setw(26) << a.am.xi.str() << " : " << a.eq);
                    }


                }

            }

        }


    }
}

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(solver)
{
    Weasel &           weasel = Weasel::Instance();
    Library            lib;
    Equilibria         eqs;
    Random::ParkMiller ran;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel(Jive::Module::OpenData(data,data),lib,eqs);
    }

    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;


    bool      verbose = true;
    XML::Log  xml(std::cerr,verbose);
    Clusters  cls(xml,eqs);

    Jive::_VFS::Apply( LocalFS::Instance(), ".", "cs[:digit:][.]png", Jive::Matching::Exactly, VFS::Entry::Base, Jive::_VFS::Remove);
    cls.renderAll("cs");

    const size_t      M = lib->size();
    CxxArray<xreal_t> C(M);
    const double      probaZ = EnvironmentConvert::To<double>("probaZ",0);
    const double      probaN = EnvironmentConvert::To<double>("probaN",0);
    Concentration::Fill(ran,C,M,probaZ,probaN);

    for(const Cluster *cl=cls->head;cl;cl=cl->next)
    {
        Solver solver(*cl);
        solver.run(xml,C,TopLevel,cls.K);
    }


}
Y_UDONE()

