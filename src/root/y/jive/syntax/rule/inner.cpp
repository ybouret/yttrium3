
#include "y/jive/syntax/rule/inner.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Inner:: ~Inner() noexcept
            {
            }

            Inner:: Inner() :
            Internal("Inner",UUID)
            {
            }

            const char *  Inner::  vizShape() const noexcept { return "box";   }
            const char *  Inner::  vizStyle() const noexcept { return "solid"; }

            Y_Jive_Syntax_Rule_Impl(Inner)
            {
                (void) framework;
                return Outcome(Rejected,Healthy,Running);
            }

        }

    }

}


