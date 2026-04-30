//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/type/fourcc.hpp"
#include "y/stream/serializable.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Pattern interface
        //
        //
        //______________________________________________________________________
        class Pattern : public Object, public Serializable
        {
        protected:
            explicit Pattern(const uint32_t)  noexcept;
            explicit Pattern(const Pattern &) noexcept;

        public:
            virtual ~Pattern() noexcept;


            virtual bool      takes(Token &, Source &) const = 0;
            virtual Pattern * clone()  const                 = 0;
            virtual bool      sound() const noexcept         = 0;
            bool              frail() const noexcept;

            size_t           emitUUID(OutputStream&) const;
            static Pattern * Load(InputStream &);
            static bool      AreEqual(const Pattern &lhs, const Pattern &rhs) noexcept;

            friend bool operator==(const Pattern &, const Pattern&) noexcept;
            friend bool operator!=(const Pattern &, const Pattern&) noexcept;


            const uint32_t uuid;
            const char     name[8];

        private:
            Y_Disable_Assign(Pattern);
        };
    }
}

#endif // !Y_Jive_Pattern_Included

