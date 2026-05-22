#include "y/jive/lexical/action.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Action:: Action(const Code & userCode) :
            //form(userForm),
            code(userCode),
            next(0),
            prev(0)
            {}

             Action:: ~Action() noexcept {}
        }

    }

}

