
#ifndef Y_Chemical_Plexus_Combinatorics_Included
#define Y_Chemical_Plexus_Combinatorics_Included 1

#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/reactive/equilibria.hpp"


namespace Yttrium
{
    namespace Coven { class StandardSurvey; }

    namespace Chemical
    {

        class Combinatorics
        {
        public:

            explicit Combinatorics(XML::Log  &,
                                   Topology   &,
                                   Equilibria &);

            virtual ~Combinatorics() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Combinatorics);
            void buildPrimary(Coven::StandardSurvey &,
                              XML::Log              &,
                              Topology              &) const;
        };
    }

}

#endif // !Y_Chemical_Plexus_Combinatorics_Included

