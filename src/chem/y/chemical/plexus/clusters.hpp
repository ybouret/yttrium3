
#ifndef Y_Chemical_Plexus_Clusters_Included
#define Y_Chemical_Plexus_Clusters_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Gathering clusters
        //
        //
        //______________________________________________________________________
        class Clusters : public Proxy<const Core::ListOf<Cluster> >
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
             \param xml for output
             \param eqs initial equilibria, updated
             \param t0  initial time evaluation
             */
            explicit Clusters(XML::Log   &  xml,
                              Equilibria &  eqs,
                              const xreal_t t0 = 0);

            //! cleanup
            virtual ~Clusters() noexcept;


            //__________________________________________________________________
            //
            //
            // Methodss
            //
            //__________________________________________________________________

            //! update all constants \param t evaluation time
            void update(const xreal_t t);

            

        private:
            Y_Disable_Copy_And_Assign(Clusters); //!< discarded
            Y_Proxy_Decl();                      //!< helper
            CxxListOf<Cluster> list;             //!< inner list
            Vector<xreal_t>    topK;             //!< top level constants

        public:
            const XReadable & K; //!< top level constant

        };
    }

}

#endif // !Y_Chemical_Plexus_Clusters_Included

