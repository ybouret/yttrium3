
//! \file

#ifndef Y_Pattern_Within_Included
#define Y_Pattern_Within_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Jive
    {
        class Within
        {
        public:
            Within(const uint8_t,const uint8_t) noexcept;
            virtual ~Within() noexcept;
            Within(const Within &) noexcept;

            const uint8_t lower;
            const uint8_t upper;

        private:
            Y_Disable_Assign(Within);
        };
    }

}

#endif // !Y_Pattern_Within_Included
