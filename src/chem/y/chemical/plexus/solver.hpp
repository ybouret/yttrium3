
//! \file

#ifndef Y_Chemical_Plexus_Solver_Included
#define Y_Chemical_Plexus_Solver_Included 1

#include "y/chemical/plexus/solver/ansatz.hpp"

namespace Yttrium
{
    namespace Chemical
    {
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
    }

}


#endif // !Y_Chemical_Plexus_Solver_Included

