
#include "y/jive/lexical/unit.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Unit:: Unit(const Spot &spot, const Identifier &uid) noexcept :
            Object(), Spot(spot), name(uid), next(0), prev(0)
            {
            }
            

            Unit:: ~Unit() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Unit &unit)
            {
                return os << unit.title << ':' << unit.line << ':' << unit.column << ": '" << (const Token &)unit << "'";
            }
        }
        
    }

}
