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

        Exception & Spot:: stamp(Exception &excp) const noexcept
        {
            return excp.pre("%s:%u:%u: ", title->c_str(),line,column);
        }


        String Spot:: str() const
        {
            return Formatted::Get("%s:%u:%u: ",title->c_str(),line,column);
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
            Coerce(line)   = 1;
            Coerce(column) = 1;
        }



    }
}
