
#ifndef Y_Chemical_Plexus_Clusters_Included
#define Y_Chemical_Plexus_Clusters_Included 1

#include "y/chemical/plexus/cluster.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Clusters : public Proxy<const Core::ListOf<Cluster> >
        {
        public:
            explicit Clusters(XML::Log   & xml,
                              Equilibria & eqs);

            virtual ~Clusters() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Clusters);
            Y_Proxy_Decl();
            CxxListOf<Cluster> list;
        };
    }

}

#endif // !Y_Chemical_Plexus_Clusters_Included

