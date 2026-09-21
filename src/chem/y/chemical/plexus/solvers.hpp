
//! \file

#ifndef Y_Chemical_Plexus_Solvers_Included
#define Y_Chemical_Plexus_Solvers_Included 1

#include "y/chemical/plexus/solver.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Solvers : public Proxy< const Core::ListOf<Solver> >
        {
        public:
            explicit Solvers(const Clusters &);
            virtual ~Solvers() noexcept;

            void run(XML::Log        & xml,
                     XWritable       & C,
                     const Level       L,
                     const XReadable & K);

        private:
            Y_Disable_Copy_And_Assign(Solvers);
            Y_Proxy_Decl();
            CxxListOf<Solver> solvers;
        };

    }

}

#endif // !Y_Chemical_Plexus_Solvers_Included

