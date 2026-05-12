


#include "y/jive/pattern/basic/excl.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Excl:: Excl(const uint8_t b) noexcept : OneChar(UUID), code(b)
        {
        }

        Excl:: Excl(const Excl &_) noexcept : OneChar(_), code(_.code) {}

        Pattern * Excl:: clone() const
        {
            return new Excl(*this);
        }



        Excl:: ~Excl() noexcept
        {
        }

        bool Excl:: found(const uint8_t b) const noexcept
        {
            return b != code;
        }

        size_t Excl:: serialize(OutputStream &fp) const
        {
            const size_t res = emitUUID(fp);
            return res + fp.cbr(code);
        }

        void Excl:: glean(Leading &leading) const noexcept
        {
            Leading tmp;
            tmp.all().clr(code);
            leading << tmp;
        }

        bool Excl:: univocal() const noexcept
        {
            return false;
        }

        OutputStream & Excl:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp,(char)code) << ",shape=doublecircle";
            return Endl(fp<<']');
        }

        Pattern * Excl:: optimized()
        {
            return this;
        }
    }

}

#include "y/jive/pattern/logic/none.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * Excl:: insensitive()
        {
            if( islower(code) )
            {
                AutoPtr<Logic> p = new None;
                *p << code;
                *p << (uint8_t) toupper(code);
                delete this;
                return p.yield();
            }

            if( isupper(code) )
            {
                AutoPtr<Logic> p = new None;
                *p << code;
                *p << (uint8_t) tolower(code);
                delete this;
                return p.yield();
            }



            return this;
        }

    }

}
