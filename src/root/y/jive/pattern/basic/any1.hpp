
//! \file

#ifndef Y_Jive_Any1_Included
#define Y_Jive_Any1_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Any1 : public Pattern
        {
        public:
            static const uint32_t UUID = Y_FOURCC('A','N','Y','1');

            explicit Any1()    noexcept;
            virtual ~Any1()    noexcept;
            Any1(const Any1 &) noexcept;

            virtual bool      takes(Token &, Source &) const;
            virtual Pattern * clone()                  const;

        private:
            Y_Disable_Assign(Any1);
        };

    }

}

#endif // !Y_Jive_Any1_Included

