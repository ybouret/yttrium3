//! \file

#ifndef Y_Jive_Spot_Included
#define Y_Jive_Spot_Included 1

#include "y/stream/identifier.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Spot
        {
        public:
            template <typename NAME> inline
            explicit Spot(const NAME &name) :
            title(name), line(1), column(1)
            {
            }

            virtual ~Spot()    noexcept;
            Spot(const Spot &) noexcept;

            Spot previous() const;

            const Identifier title;
            const unsigned   line;
            const unsigned   column;

        private:
            Y_Disable_Assign(Spot);
        };

    }
}


#endif // !Y_Jive_Spot_Included

