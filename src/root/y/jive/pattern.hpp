//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Pattern : public Object
        {
        private:
            explicit Pattern(const uint32_t)  noexcept;
            explicit Pattern(const Pattern &) noexcept;

        public:
            virtual ~Pattern() noexcept;


            virtual bool accepts(Token &token, Source &source) const = 0;

            const uint32_t uuid;
            const char     name[8];

        private:
            Y_Disable_Assign(Pattern);
        };
    }
}

#endif // !Y_Jive_Pattern_Included

