
#include "y/jive/lexical/unit.hpp"
#include "y/exception.hpp"

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
                return os
                << unit.title << ':' << unit.line << ':' << unit.column << ':'
                << " [" << unit.name << "]"
                << " '" << (const Token &)unit << "'";
            }

            Exception & Unit:: addTo(Exception &excp, const bool full) const noexcept
            {
                excp.cat("'%s'",name->c_str());
                if(full && size) {
                    const Token &self = *this;
                    const String data = self.str();
                    excp.cat("='%s'",data.c_str());
                }
                return excp;
            }
        }
        
    }

}
