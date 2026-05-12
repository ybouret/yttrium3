

#include "y/jive/pattern/basic/byte.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Byte:: Byte(const uint8_t b) noexcept : OneChar(UUID), code(b)
        {
        }

        Byte:: Byte(const Byte &_) noexcept : OneChar(_), code(_.code) {}

        Pattern * Byte:: clone() const
        {
            return new Byte(*this);
        }



        Byte:: ~Byte() noexcept
        {
        }

        bool Byte:: found(const uint8_t b) const noexcept
        {
            return b == code;
        }

        size_t Byte:: serialize(OutputStream &fp) const
        {
            const size_t res = emitUUID(fp);
            return res + fp.cbr(code);
        }

        void Byte:: glean(Leading &leading) const noexcept
        {
            leading << code;
        }

        bool Byte:: univocal() const noexcept
        {
            return true;
        }

        OutputStream & Byte:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp,(char)code) << ",shape=circle";
            return Endl(fp<<']');
        }

        Pattern * Byte:: optimized()
        {
            return this;
        }
    }

}

#include "y/jive/pattern/logic/or.hpp"
#include "y/pointer/auto.hpp"
#include <cctype>

namespace Yttrium
{
    namespace Jive
    {
        Pattern * Byte:: insensitive()
        {
            if( islower(code) )
            {
                AutoPtr<Logic> p = new Or();
                *p << code;
                *p << (uint8_t) toupper(code);
                delete this;
                return p.yield();
            }

            if( isupper(code) )
            {
                AutoPtr<Logic> p = new Or();
                *p << code;
                *p << (uint8_t) tolower(code);
                delete this;
                return p.yield();
            }

            return this;
        }
    }

}
