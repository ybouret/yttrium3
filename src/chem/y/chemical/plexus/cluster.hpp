//! \file

#ifndef Y_Chemical_Plexus_Cluster_Included
#define Y_Chemical_Plexus_Cluster_Included 1

#include "y/chemical/plexus/conservations.hpp"
#include "y/chemical/plexus/conservation/canons.hpp"
#include "y/chemical/plexus/conservation/adjudicator.hpp"

#include "y/chemical/plexus/combinatorics.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Independant cluster of dependent equilibria
        //
        //
        //______________________________________________________________________
        class Cluster : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
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

            //! cleanup
            virtual ~Cluster() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            OutputStream & viz(OutputStream &, const size_t order) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Topology             topology;       //!< topology (from partition)
            const Conservations        conservations;  //!< conservation laws
            const Conservation::Canons canons;         //!< conservation canons
            const Combinatorics        combinatorics;  //!< combinatorics
            Cluster *                  next;           //!< for list
            Cluster *                  prev;           //!< for list
            const size_t               gvid;           //!< GrapViz ID

        private:
            Y_Disable_Copy_And_Assign(Cluster); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Plexus_Cluster_Included

