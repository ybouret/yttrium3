


//! \file

#ifndef Y_Jive_Range_Included
#define Y_Jive_Range_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Range : public OneChar
        {
        public:
            static const uint32_t UUID = Y_FOURCC('R','N','G','E');

            explicit Range(const uint8_t,const uint8_t) noexcept;
            virtual ~Range()                            noexcept;
            Range(const Range &)                        noexcept;

            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;
            virtual void      glean(Leading &) const noexcept;

            const uint8_t lower;
            const uint8_t upper;

        private:
            Y_Disable_Assign(Range);
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Range_Included

