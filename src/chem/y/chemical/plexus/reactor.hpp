
//! \file

#ifndef Y_Chemical_Plexus_Reactor_Included
#define Y_Chemical_Plexus_Reactor_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/reactive/erepo.hpp"

#include "y/chemical/plexus/reactor/assay.hpp"
#include "y/chemical/plexus/reactor/resources.hpp"

#include "y/container/cxx/series.hpp"

#include "y/coven/finder.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        
        class Reactor : public Object
        {
        public:
            static const char * const StdProfileExt; //!< "ycp"
            static const char * const OptProfileExt; //!< "yop"

            enum Outcome
            {
                Improved,
                Achieved,
                Spurious
            };

            static bool     Trace;
            static unsigned TracePoints;

            explicit Reactor(const Cluster &);
            virtual ~Reactor() noexcept;


            Outcome run(XML::Log &xml,
                        XWritable &C,
                        const Level L,
                        const XReadable &K);


            xreal_t ObjectiveFunction(const XReadable &, const Level);
            xreal_t operator()(const xreal_t);


            void          saveProfile(OutputStream &);
            static String MakeFileName(const String &);

            static void TryRemoveProfiles(const String &dirName);


            const Cluster &    cluster;   //!< attached cluster
            const size_t  &    N;         //!< original number of equilibria
            const size_t  &    M;         //!< number of reactive species
            const size_t  &    n;         //!< total number of equilibria
            xreal_t            F0;        //!< initial objective function at Cini
            XArray             Cini;      //!< initial   SubLevel concentrations
            XArray             Cend;      //!< end point SubLevel concentrations
            XArray             Ctry;      //!< trial     SubLevel concentrations
            XMatrix            Ceq;       //!< 1D solutions [n:M]
            CxxSeries<Assay>   assays;    //!< selected equilibria
            XMul               xmul;      //!< for inner mul
            XAdd               xadd;      //!< for inner add
            XAdd               fadd;      //!< for objective function
            AutoPtr<Resources> resources; //!< numeric resources

        private:
            Y_Disable_Copy_And_Assign(Reactor);
            size_t buildAssays(XML::Log &, XWritable &, const Level, const XReadable &);
            size_t studyAssays(XML::Log &);
            void   updateAssay(XML::Log &, Assay &, XTriplet &, XTriplet &);

        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Included

