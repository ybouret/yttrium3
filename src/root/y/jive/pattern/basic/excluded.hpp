//! \file

#ifndef Y_Jive_Excluded_Included
#define Y_Jive_Excluded_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Excluded : public OneChar
        {
        public:
            static const uint32_t UUID = Y_FOURCC('E','X','C','L');

            explicit Excluded(const uint8_t) noexcept;
            virtual ~Excluded()              noexcept;
            Excluded(const Excluded &)       noexcept;

            virtual Pattern * clone()             const;

            const uint8_t code;

        private:
            Y_Disable_Assign(Excluded);
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Excluded_Included

