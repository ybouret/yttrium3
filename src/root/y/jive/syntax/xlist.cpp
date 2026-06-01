#include "y/jive/syntax/xlist.hpp"
#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            XList:: ~XList() noexcept
            {
            }

            XList:: XList() noexcept
            {
            }

            void XList:: returnTo(Lexical::Stack &stack) noexcept
            {
                while(size) {
                    tail->returnTo(stack);
                    delete popTail();
                }
            }

        }
    }
}
