
#include "y/jive/syntax/rule/wildcard/option.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Option:: ~Option() noexcept
            {
            }

            static const char OptSymbol = '?';

            Option:: Option(const Rule &source) :
            Wildcard(new String(source.name->c_str(),source.name->size(), &OptSymbol, 1),UUID,source)
            {
            }


        }

    }

}
