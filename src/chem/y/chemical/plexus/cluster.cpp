
#include "y/chemical/plexus/cluster.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Cluster:: ~Cluster() noexcept
        {
            
        }

        Cluster:: Cluster(XML::Log     & xml,
                          const EGroup & grp,
                          Equilibria   & eqs,
                          XWritable    & tlK) :
        topology(xml,grp),
        conservations(xml,topology),
        canons(xml,conservations.laws,topology,conservations.lfmt),
        combinatorics(xml,Coerce(topology),eqs,tlK),
        next(0),
        prev(0),
        gvid(0)
        {

        }

    }

}
