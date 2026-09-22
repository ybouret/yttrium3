
//! \file

#ifndef Y_Chemical_Plexus_Solver_Included
#define Y_Chemical_Plexus_Solver_Included 1

#include "y/chemical/plexus/solver/assets.hpp"
#include "y/chemical/plexus/solver/ansatz.hpp"
#include "y/chemical/reactive/erepo.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        //______________________________________________________________________
        //
        //
        //
        //! Solver for one Cluster
        //
        //
        //______________________________________________________________________
        class Solver : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static bool                       Trace;     //!< emit profiles
            static unsigned                   TracePoints; //!< points per profile
            typedef MKL::Minimize             Minimize;  //!< alias
            static const char * const         StdProfileExt; //!< "ycp"
            static const char * const         OptProfileExt; //!< "yop"
            static const char * const         AnyProfileExt; //!< "y[c|o]p"
            static const real_t               DefaultSafety; //!< 0.95

            enum Outcome
            {
                Improved,
                Achieved,
                Spurious
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Solver(const Cluster &); //!< setup from cluster
            virtual ~Solver() noexcept;       //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Outcome run(XML::Log        & xml,
                        XWritable       & C,
                        const Level       L,
                        const XReadable & K);

            void steady(XML::Log        & xml,
                        XWritable       & C,
                        const Level       L,
                        const XReadable & K,
                        const size_t      maxCycles = 0);


            xreal_t F(const XReadable &C, const Level L);
            xreal_t operator()(const xreal_t u);

            void        saveProfile(OutputStream &, const unsigned np);
            String      MakeFileName(const String &);

            static void TryRemoveProfiles(const String & dirName, const char * const profileExt);
            static void TryRemoveRunStats(const String & dirName);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Cluster &    cls;    //!< attached cluster
            XMatrix            Ceq;     //!< 1D solutions storage
            XArray             Cini;    //!< SubLevel array
            XArray             Cend;    //!< SubLevel array
            XArray             Ctry;    //!< SubLevel trial
            XArray             dC;      //!< SubLevel Newton step
            xreal_t            Fg;      //!< NRstep result, global step
            Ansatz::Series     ans;     //!< possible ansatz
            ERepo              blk;     //!< blokced
            XMul               xmul;    //!< for inner multiplication
            XAdd               xadd;    //!< for inner additions
            XAdd               Fadd;    //!< for F computation
            const xreal_t      expand;  //!< Newton Step max expand : 2.0
            const xreal_t      safety;  //!< Newton Step safety cut : DefaultSafety
            AutoPtr<Assets>    assets;  //!< assets for computations
            Solver *           next;
            Solver *           prev;
            String             trace;   //!< gnuplot
            String             tropt;   //!< gnuplot, optimized profiles
            const String       runfn;   //!< run file name solverID.dat

        private:
            Y_Disable_Copy_And_Assign(Solver); //!< discarded

            //! regularize concentrations
            /**
             build ansatz and blocked equilibria list
             \return number of valid ansatzs
             */
            size_t regularize(XML::Log &, XWritable &, const Level, const XReadable &);

            //! regularize, then build basis from independent eqs
            size_t buildBasis(XML::Log &, XWritable &, const Level, const XReadable &);

            //! optimize ansatz over the full affinity
            /**
             \param xml output
             \param a   ansatz to optimize
             \param F0  initial start
             \param i   ansatz index (for trace)
             \return true if local minimum is found
             */
            bool optimizing(XML::Log      &xml,
                            Ansatz        &a,
                            const xreal_t F0,
                            const size_t  i);

            //! upgrade ansatz minimum
            void upgrade(XML::Log &xml,
                         Ansatz   &,
                         XTriplet &,
                         XTriplet &);


            //! compute Newton-Raphson step from Affinity
            /**
             \param xml output
             \param C   starting point
             \param L   starting level
             \return true is not singular, computed into dC
             */
            bool computeStep(XML::Log        & xml,
                             const XReadable & C,
                             const Level       L);

            void approveStep(XML::Log        & xml);


            bool NRStep(XML::Log        & xml,
                        const xreal_t     F0,
                        const XReadable & C,
                        const Level       L);


        };
    }

}


#endif // !Y_Chemical_Plexus_Solver_Included

