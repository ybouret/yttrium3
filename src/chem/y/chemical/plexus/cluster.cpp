
#include "y/chemical/plexus/cluster.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Cluster:: ~Cluster() noexcept
        {
            
        }

        Cluster:: Cluster(XML::Log     & xml,
                          const EGroup & grp) :
        topology(xml,grp),
        conservations(xml,topology),
        canons(xml,conservations.laws,topology,conservations.lfmt),
        next(0),
        prev(0)
        {
        }

    }

}
