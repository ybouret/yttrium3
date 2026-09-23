
//! \file

#ifndef Y_Chemical_Plexus_Reactor_Included
#define Y_Chemical_Plexus_Reactor_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/handy/plain/light/list.hpp"

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
            static const real_t       DefaultSafety; //!< 0.95

            static bool     TracePro;
            static bool     TraceRun;
            static unsigned TracePoints;

            typedef Handy::PlainLightList<const Assay> ARepo;
            typedef ARepo::NodeType                    ANode;

            enum Outcome
            {
                Improved,
                Achieved,
                Spurious
            };



            explicit Reactor(const Cluster &);
            virtual ~Reactor() noexcept;


            Outcome run(XML::Log        & xml,
                        XWritable       & C,
                        const Level       L,
                        const XReadable & K);

            bool transform(XML::Log &xml,
                           XWritable       & C,
                           const Level       L,
                           const XReadable & K,
                           const size_t      maxCycle);


            xreal_t ObjectiveFunction(const XReadable &, const Level);
            xreal_t operator()(const xreal_t);


            void          saveProfile(OutputStream &);
            static String MakeFileName(const String &);

            static void TryRemoveProfiles(const String &dirName);
            static void TryRemoveRunStats(const String &dirName);

            const Cluster &    cluster;   //!< attached cluster
            const size_t  &    N;         //!< original number of equilibria
            const size_t  &    M;         //!< number of reactive species
            const size_t  &    n;         //!< total number of equilibria
            xreal_t            F0;        //!< initial objective function at Cini
            xreal_t            Fs;        //!< objective function from NR step
            XArray             Cini;      //!< initial   SubLevel concentrations
            XArray             Cend;      //!< end point SubLevel concentrations
            XArray             Ctry;      //!< trial     SubLevel concentrations
            XArray             dC;        //!< from NR step
            XMatrix            Ceq;       //!< 1D solutions [n:M]
            ARepo              basis;     //!< basis
            CxxSeries<Assay>   assays;    //!< selected equilibria
            XMul               xmul;      //!< for inner mul
            XAdd               xadd;      //!< for inner add
            XAdd               fadd;      //!< for objective function
            const xreal_t      expand;  //!< Newton Step max expand : 2.0
            const xreal_t      safety;  //!< Newton Step safety cut : DefaultSafety
            AutoPtr<Resources> resources; //!< numeric resources
            String             gpStd;
            String             gpOpt;

        private:
            Y_Disable_Copy_And_Assign(Reactor);
            size_t buildAssays(XML::Log &, XWritable &, const Level, const XReadable &);
            size_t studyAssays(XML::Log &);
            void   updateAssay(XML::Log &, Assay &, XTriplet &, XTriplet &);
            void   createBasis(XML::Log &);
            bool   computeStep(XML::Log &);
            void   approveStep(XML::Log &);
            bool   builtNRStep(XML::Log &);
        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Included

