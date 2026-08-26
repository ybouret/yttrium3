
#ifndef Y_Chemical_Plexus_Clusters_Included
#define Y_Chemical_Plexus_Clusters_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/container/sequence/vector.hpp"

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

            //! compute all constants \param t evaluation time
            const XReadable & K(const xreal_t t);

        private:
            Y_Disable_Copy_And_Assign(Clusters);
            Y_Proxy_Decl();
            CxxListOf<Cluster> list;
            Vector<xreal_t>    topK;


        };
    }

}

#endif // !Y_Chemical_Plexus_Clusters_Included

