
//! \file

#ifndef Y_Chemical_Plexus_Solver_Included
#define Y_Chemical_Plexus_Solver_Included 1

#include "y/chemical/plexus/solver/ansatz.hpp"
#include "y/coven/finder.hpp"

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
            typedef AutoPtr<Coven::Finder> Finder; //!< alias
            static bool                    Trace;  //!< emit profiles

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Solver(const Cluster &cluster);
            virtual ~Solver() noexcept;

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
            xreal_t F(const xreal_t u);

            void   saveProfile(OutputStream &, const unsigned np);
            String MakeFileName(const String &);


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
            XMul               xmul;   //!< for inner multiplication
            XAdd               xadd;   //!< for inner additions
            XAdd               Fadd;   //!< for F computation
            CxxSeries<XMatrix> jac;    //!< preformated matrices
            Finder             finder; //!< helper to build basis

        private:
            Y_Disable_Copy_And_Assign(Solver); //!< discarded

            //! regularize concentrations, return number of valid ansatzs
            size_t regularize(XML::Log &, XWritable &, const Level, const XReadable &);

            //! regularize, then build basis from independent eqs
            size_t buildBasis(XML::Log &, XWritable &, const Level, const XReadable &);

            bool   optimizing(XML::Log &,
                              const Ansatz &a,
                              const xreal_t F0,
                              const size_t  i);


        };
    }

}


#endif // !Y_Chemical_Plexus_Solver_Included

