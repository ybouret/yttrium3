
#ifndef Y_Chemical_Plexus_Canon_Included
#define Y_Chemical_Plexus_Canon_Included 1

#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/plexus/conservation/law.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Matrix<unsigned> UMatrix;

        class Canon
        {
        public:
            typedef Conservation::Law Law;
            typedef Law::List         Laws;

            explicit Canon(XML::Log &, const Topology &);
            virtual ~Canon() noexcept;
            
            const UMatrix Qm;
            const Laws    laws;

        private:
            Y_Disable_Copy_And_Assign(Canon);
        };

    }

}

#endif // !Y_Chemical_Plexus_Canon_Included

