
//! \file

#ifndef Y_Jive_Leading_Included
#define Y_Jive_Leading_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Leading
        {
        public:
            static const uint8_t Bit[8];
            static const uint8_t Msk[8];

            Leading()                            noexcept;
            ~Leading()                           noexcept;
            Leading(const Leading &)             noexcept;
            Leading & operator=(const Leading &) noexcept;
            Y_OSTREAM_PROTO(Leading);

            Leading & operator << (const uint8_t)   noexcept;
            Leading & operator << (const Leading &) noexcept;

            bool get(const uint8_t) const noexcept;
            Leading & set(const uint8_t) noexcept;
            Leading & clr(const uint8_t) noexcept;
            Leading & set(const uint8_t lo, const uint8_t up) noexcept;
            Leading & ldz() noexcept;
            Leading & all() noexcept;

            size_t size() const noexcept;


        private:
            uint8_t data[32];
        };
    }

}

#endif // !Y_Jive_Leading_Included
