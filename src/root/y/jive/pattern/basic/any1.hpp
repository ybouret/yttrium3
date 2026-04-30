
//! \file

#ifndef Y_Jive_Any1_Included
#define Y_Jive_Any1_Included 1

#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Any1 : public OneChar
        {
        public:
            static const uint32_t UUID = Y_FOURCC('A','N','Y','1');

            explicit Any1()    noexcept;
            virtual ~Any1()    noexcept;
            Any1(const Any1 &) noexcept;

            virtual Pattern * clone()                   const;
            virtual size_t    serialize(OutputStream &) const;

        private:
            Y_Disable_Assign(Any1);
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Any1_Included

