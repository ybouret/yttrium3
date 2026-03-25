
#include "y/xml/element.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace XML
    {
        Element:: Element(const char * const  userTag,
                          Log               & userOut,
                          const bool          userOne,
                          const bool          userAtr) noexcept :
        tag(userTag),
        out(userOut),
        one(userOne),
        atr(userAtr)
        {
            assert(userTag);

            if(out.verbose)
            {
                std::ostream & os = prolog();
                if(userAtr)
                {
                    
                }
            }

            ++out.level;
        }


        Element:: ~Element() noexcept
        {
            --out.level;

        }

        std::ostream & Element:: prolog()
        {
            if(out.verbose)
            {
                out() << LANGLE << tag;
            }
            return *out;
        }

    }

}
