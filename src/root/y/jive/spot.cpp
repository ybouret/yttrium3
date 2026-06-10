#include "y/jive/spot.hpp"
#include "y/exception.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Spot:: ~Spot() noexcept
        {
        }

        Spot:: Spot(const Spot &spot) noexcept :
        title(spot.title),
        line(spot.line),
        column(spot.column)
        {
        }

        namespace
        {
            static const char * const SpotFmt = "%s:%u:%u: ";
        }

        Exception & Spot:: stamp(Exception &excp) const noexcept
        {
            return excp.pre(SpotFmt, title->c_str(),line,column);
        }


        String Spot:: stamp() const
        {
            return Formatted::Get(SpotFmt,title->c_str(),line,column);
        }

        Spot & Spot:: operator=(const Spot &spot) noexcept
        {
            { Identifier temp(spot.title); Coerce(title).xch(temp); }
            Coerce(line)   = spot.line;
            Coerce(column) = spot.column;
            return *this;
        }

        void Spot:: set(const Identifier &id) noexcept
        {
            { Identifier temp(id); Coerce(title).xch(temp); }
            Coerce(line)   = DefaultLine;
            Coerce(column) = DefaultColumn;
        }



    }
}
