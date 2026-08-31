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
        class Cluster : public Object,
        public Topology,
        public Conservations,
        public Combinatorics
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

            //! display given grade
            /**
             if(1==gr) then conservations are emitted
             \param os output stream
             \param gr grade in [1:grade.size()]
             \return os
             */
            OutputStream & viz(OutputStream &os, const size_t gr) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Conservation::Canons canons;         //!< conservation canons
            Cluster *                  next;           //!< for list
            Cluster *                  prev;           //!< for list
            const size_t               gvid;           //!< GrapViz ID

        private:
            Y_Disable_Copy_And_Assign(Cluster); //!< discarded
            Topology & _topo() noexcept;        //!< helper \return *this*
        };
    }

}

#endif // !Y_Chemical_Plexus_Cluster_Included

