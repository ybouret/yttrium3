
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
            //! setup
            /**
             \param xml output
             \param grp independant group of dependent equilibria
             \param eqs database of equilibria
             \param tlK Top Level Constants
             */
            explicit Cluster(XML::Log     & xml,
                             const EGroup & grp,
                             Equilibria   & eqs,
                             XWritable    & tlK);

            virtual ~Cluster() noexcept;

            const Topology             topology;
            const Conservations        conservations;
            const Conservation::Canons canons;
            const Combinatorics        combinatorics;

            Cluster * next;
            Cluster * prev;
            
        private:
            Y_Disable_Copy_And_Assign(Cluster);
        };
    }

}

#endif // !Y_Chemical_Plexus_Cluster_Included

