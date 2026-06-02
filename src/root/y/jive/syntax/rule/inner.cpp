
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

            OutputStream & Inner:: vizSelf(OutputStream &fp) const
            {
                return fp;
            }

            Y_Jive_Syntax_Rule_Impl(Inner)
            {
                
            }

        }

    }

}


