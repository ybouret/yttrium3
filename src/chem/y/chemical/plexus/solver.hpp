
//! \file

#ifndef Y_Chemical_Plexus_Solver_Included
#define Y_Chemical_Plexus_Solver_Included 1

#include "y/chemical/plexus/solver/ansatz.hpp"
#include "y/coven/finder.hpp"
#include "y/mkl/minimize/api.hpp"
#include "y/chemical/reactive/erepo.hpp"
#include "y/mkl/algebra/lu.hpp"

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
        class Solver
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef AutoPtr<Coven::Finder>    Finder;    //!< alias
            static bool                       Trace;     //!< emit profiles
            static unsigned                   TracePoints; //!< points per profile
            typedef MKL::Minimize             Minimize;  //!< alias
            typedef Minimize::Engine<xreal_t> Optimizer; //!< alias
            static const char * const         StdProfileExt; //!< "ycp"
            static const char * const         OptProfileExt; //!< "yop"
            static const char * const         AnyProfileExt; //!< "y[c|o]p"

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
            void run(XML::Log        & xml,
                     XWritable       & C,
                     const Level       L,
                     const XReadable & K);

            xreal_t F(const XReadable &C, const Level L);
            xreal_t operator()(const xreal_t u);

            void   saveProfile(OutputStream &, const unsigned np);
            String MakeFileName(const String &);

            static void TryRemoveProfiles(const String & dirName, const char * const profileExt);


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Cluster &    cls;    //!< attached cluster

            XMatrix            Ceq;    //!< 1D solutions storage
            XArray             Cini;   //!< SubLevel array
            XArray             Cend;   //!< SubLevel array
            XArray             Ctry;   //!< SubLevel trial
            Ansatz::Series     ans;    //!< possible ansatz
            ERepo              blk;    //!< blokced
            XMul               xmul;   //!< for inner multiplication
            XAdd               xadd;   //!< for inner additions
            XAdd               Fadd;   //!< for F computation
            const xreal_t      xl10;   //!< log(10)
            Optimizer          opt;
            MKL::LU<xreal_t>   lu;  
            Finder             finder; //!< helper to build basis
            CxxSeries<XMatrix> jac;    //!< preformated matrices
            String             trace;  //!< gnuplot
            String             tropt;  //!< gnuplot, optimized profiles
            
        private:
            Y_Disable_Copy_And_Assign(Solver); //!< discarded

            //! regularize concentrations, return number of valid ansatzs
            size_t regularize(XML::Log &, XWritable &, const Level, const XReadable &);

            //! regularize, then build basis from independent eqs
            size_t buildBasis(XML::Log &, XWritable &, const Level, const XReadable &);

            bool   optimizing(XML::Log      &xml,
                              Ansatz        &a,
                              const xreal_t F0,
                              const size_t  i);


            void upgrade(XML::Log &xml,
                         Ansatz   &,
                         XTriplet &,
                         XTriplet &);


        };
    }

}


#endif // !Y_Chemical_Plexus_Solver_Included

