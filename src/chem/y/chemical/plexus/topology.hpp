#ifndef Y_Chemical_Plexus_Topology_Included
#define Y_Chemical_Plexus_Topology_Included 1

#include "y/chemical/reactive/equilibrium/group.hpp"
#include "y/chemical/reactive/equilibrium/format.hpp"
#include "y/container/matrix.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Matrix<int> IMatrix;
        typedef Handy::BasicLightList<const Species> SList;
        typedef SList::NodeType                      SNode;

        class Topology
        {
        public:
            explicit Topology(XML::Log &, const EList &);
            virtual ~Topology() noexcept;

            const EList   & group; //!< original equilibria
            const EList     elist; //!< equilibria
            const SList     slist; //!< species
            const IMatrix   nu;    //!< topology
            const size_t &  N;
            const size_t &  M;

            const EqFormat  efmt;
            const Assembly  sfmt;

        private:
            Y_Disable_Copy_And_Assign(Topology);
        };

    }

}

#endif // !Y_Chemical_Plexus_Topology_Included

