
#include "y/jive/syntax/rule/wildcard.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Wildcard:: ~Wildcard() noexcept
            {
            }


            OutputStream & Wildcard:: vizLink(OutputStream &fp) const
            {
                return Endl( to(&rule,fp) );
            }
        }

    }

}
