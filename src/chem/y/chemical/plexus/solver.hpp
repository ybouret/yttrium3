
//! \file

#ifndef Y_Chemical_Plexus_Solver_Included
#define Y_Chemical_Plexus_Solver_Included 1

#include "y/chemical/plexus/solver/ansatz.hpp"
#include "y/coven/finder.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Solver
        {
        public:
            typedef AutoPtr<Coven::Finder> Finder;
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
            Finder         finder;

        private:
            Y_Disable_Copy_And_Assign(Solver);
        };
    }

}


#endif // !Y_Chemical_Plexus_Solver_Included

