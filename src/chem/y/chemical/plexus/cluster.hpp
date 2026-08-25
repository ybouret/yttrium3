
#ifndef Y_Chemical_Plexus_Cluster_Included
#define Y_Chemical_Plexus_Cluster_Included 1

#include "y/chemical/reactive/equilibrium/partition.hpp"
#include "y/chemical/plexus/conservations.hpp"
#include "y/chemical/plexus/conservation/canons.hpp"
#include "y/chemical/plexus/conservation/adjudicator.hpp"

#include "y/chemical/plexus/combinatorics.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Cluster : public Object
        {
        public:

            explicit Cluster(XML::Log     & xml,
                             const EGroup & grp);

            virtual ~Cluster() noexcept;

            const Topology             topology;
            const Conservations        conservations;
            const Conservation::Canons canons;

            Cluster * next;
            Cluster * prev;
            
        private:
            Y_Disable_Copy_And_Assign(Cluster);
        };
    }

}

#endif // !Y_Chemical_Plexus_Cluster_Included

