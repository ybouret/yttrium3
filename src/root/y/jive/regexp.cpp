
#include "y/jive/regexp.hpp"
#include "y/jive/regexp/compiler.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compile_(const Identifier &       content,
                                    const Dictionary * const dict)
        {


            RXCompiler rx(content->c_str(),content->size(),dict);
            
            return 0;
        }
    }

}
