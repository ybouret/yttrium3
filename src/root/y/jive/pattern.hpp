//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Pattern : public Object
        {
        protected:
            explicit Pattern(const uint32_t)  noexcept;
            explicit Pattern(const Pattern &) noexcept;

        public:
            virtual ~Pattern() noexcept;


            virtual bool      takes(Token &, Source &) const = 0;
            virtual Pattern * clone()  const                 = 0;
            virtual bool      sound() const noexcept        = 0;
            bool              frail() const noexcept;

            const uint32_t uuid;
            const char     name[8];

        private:
            Y_Disable_Assign(Pattern);
        };
    }
}

#endif // !Y_Jive_Pattern_Included

