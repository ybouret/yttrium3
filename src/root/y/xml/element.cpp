
#include "y/xml/element.hpp"
#include <iostream>
#include <cassert>
#include <cstdarg>

namespace Yttrium
{
    namespace XML
    {
        Element:: Element(Log               & userOut,
                          const char * const  userTag,
                          const bool          userOne) :
        out(userOut),
        tag(userTag),
        one(userOne)
        {
            assert(userTag);

            if(out.verbose)
            {
                out() << LANGLE << tag;
            }

            ++out.level;
        }

        void Element:: end()
        {
            if(out.verbose)
            {
                if(one)
                {
                    *out << SLASH;
                }
                *out << RANGLE << std::endl;
            }
        }

        Element & Element:: operator<<(const Attribute attr)
        {
            if(out.verbose) *out << attr;
            return *this;
        }


        Element:: ~Element() noexcept
        {
            --out.level;
            if(out.verbose)
            {
                if(!one)
                {
                    out() << LANGLE << SLASH << tag << RANGLE << std::endl;
                }
            }
        }




    }

}
