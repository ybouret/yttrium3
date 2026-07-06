
#ifndef Y_Chemical_Conservation_PCoef_Included
#define Y_Chemical_Conservation_PCoef_Included 1

#include "y/chemical/species.hpp"
#include "y/chemical/type/defs.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            class PCoef : public Object
            {
            public:
                typedef CxxListOf<PCoef> List;
                explicit PCoef(const xreal_t, const Species &) noexcept;
                virtual ~PCoef() noexcept;
                Y_OSTREAM_PROTO(PCoef);

                const PCoef & operator*() const noexcept;
                
                const xreal_t  cf;
                const Species &sp;
                PCoef         *next;
                PCoef         *prev;

            private:
                Y_Disable_Copy_And_Assign(PCoef);
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_PCoef_Included

