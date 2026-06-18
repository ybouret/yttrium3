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

        //______________________________________________________________________
        //
        //
        //
        //! Topology from a given list of connected equilibria
        //
        //
        //______________________________________________________________________
        class Topology
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Topology(XML::Log &, const EList &); //!< setup
            virtual ~Topology() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const EList   & group; //!< original equilibria
            const EList     elist; //!< equilibria
            const SList     slist; //!< species
            const IMatrix   nu;    //!< topology
            const IMatrix   nuT;   //!< topology'
            const size_t &  N;     //!< number of equilbira
            const size_t &  M;     //!< number of species
            const EqFormat  efmt;  //!< helper to format equilibria
            const Assembly  sfmt;  //!< helper to format species

        private:
            Y_Disable_Copy_And_Assign(Topology); //!< discarded
        };

    }

}

#endif // !Y_Chemical_Plexus_Topology_Included

