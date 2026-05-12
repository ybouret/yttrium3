
#include "y/jive/regexp.hpp"
#include "y/jive/regexp/compiler.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compile_(const Identifier &       content,
                                    const Dictionary * const dict)
        {

            RXCompiler       rxc(content->c_str(),content->size(),dict);
            AutoPtr<Pattern> rx = rxc();
            return rx.yield();
        }
    }

}
