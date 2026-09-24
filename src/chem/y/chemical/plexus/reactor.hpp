
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

        //______________________________________________________________________
        //
        //
        //
        //! Reactor for a Cluster
        //
        //
        //______________________________________________________________________
        class Reactor : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const char * const StdProfileExt; //!< "ycp"
            static const char * const OptProfileExt; //!< "yop"
            static const real_t       DefaultSafety; //!< 0.95

            static bool     TracePro;    //!< enable to save profile
            static bool     TraceRun;    //!< enable to save run values
            static unsigned TracePoints; //!< points per profile

            typedef Handy::PlainLightList<const Assay> ARepo; //!< alias
            typedef ARepo::NodeType                    ANode; //!< alias

            //! run outcome value
            enum Outcome
            {
                Improved, //!< decreased value
                Achieved, //!< convergence
                Spurious  //!< no more decrease
            };


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Reactor(const Cluster &); //!< setup
            virtual ~Reactor() noexcept;       //!< cleanp

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! run an algorithm step
            /**
             \param xml output
             \param C   [in|out] state
             \param L   state level
             \param K   TopLevel K
             \return run outcome
             */
            Outcome run(XML::Log        & xml,
                        XWritable       & C,
                        const Level       L,
                        const XReadable & K);

            //! best effort run
            /**
             \param xml      output
             \param C        [in|out] state
             \param L        state level
             \param K        TopLevel K
             \param maxCycle positive to debug
             \return true if convergence, false if spurious, saved into 'last'
             */
            bool transform(XML::Log        & xml,
                           XWritable       & C,
                           const Level       L,
                           const XReadable & K,
                           const size_t      maxCycle);


            //! \return value at given coordinate
            xreal_t ObjectiveFunction(const XReadable &, const Level);

            //! \return value in [Cini:Cend]
            xreal_t operator()(const xreal_t);

            //! \return convergence of states
            bool convergence(const XReadable &, const Level,
                             const XReadable &, const Level) const noexcept;


            void          saveProfile(OutputStream &);  //!< save profile to output
            static String MakeFileName(const String &); //!< equilibrium name to file name

            static void TryRemoveProfiles(const String &dirName); //!< remove extension "y[c|o]p"      \param dirName working directory
            static void TryRemoveRunStats(const String &dirName); //!< remove "solver[:digit:]+[.]dat" \param dirName working directory

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
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
            const bool         last;      //!< last transform result
            const xreal_t      expand;    //!< Newton Step max expand : 2.0
            const xreal_t      safety;    //!< Newton Step safety cut : DefaultSafety
            AutoPtr<Resources> resources; //!< numeric resources
            Reactor *          next;      //!< for list
            Reactor *          prev;      //!< for list
            String             gpStd;     //!< gnuplot command when TracePro is activated
            String             gpOpt;     //!< gnuplot command when TracePro is activated

        private:
            Y_Disable_Copy_And_Assign(Reactor); //!< discard

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            size_t buildAssays(XML::Log &, XWritable &, const Level, const XReadable &);
            size_t studyAssays(XML::Log &);
            void   updateAssay(XML::Log &, Assay &, XTriplet &, XTriplet &);
            void   createBasis(XML::Log &);
            bool   computeStep(XML::Log &);
            void   approveStep(XML::Log &);
            bool   builtNRStep(XML::Log &);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Included

