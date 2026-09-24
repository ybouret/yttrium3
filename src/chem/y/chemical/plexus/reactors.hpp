
//! \file

#ifndef Y_Chemical_Plexus_Reactors_Included
#define Y_Chemical_Plexus_Reactors_Included 1

#include "y/chemical/plexus/reactor.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        class Reactors : public Proxy< const Core::ListOf<Reactor> >
        {
        public:
            explicit Reactors(const Clusters &);
            virtual ~Reactors() noexcept;

            void operator()(XML::Log  & xml,
                            XWritable & C,
                            const Level L,
                            const size_t maxCycle = 0);

        private:
            Y_Disable_Copy_And_Assign(Reactors);
            Y_Proxy_Decl();
            const Clusters     & clusters;
            CxxListOf<Reactor>   reactors;

        };

    }

}

#endif // !Y_Chemical_Plexus_Reactors_Included


