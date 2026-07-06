
#ifndef Y_Chemical_Conservation_Adjudicator_Included
#define Y_Chemical_Conservation_Adjudicator_Included 1

#include "y/chemical/plexus/conservation/canon.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            class Adjudicator
            {
            public:

                explicit Adjudicator(const Canon &);
                virtual ~Adjudicator() noexcept;

                const Canon    &canon;
                const size_t    n;       //!< number of laws
                const size_t    m;       //!< number of species
                Matrix<xreal_t> C;       //!< workspace
                
            private:
                Y_Disable_Copy_And_Assign(Adjudicator);
                
            };

        }

    }

}

#endif // !Y_Chemical_Conservation_Adjudicator_Included

