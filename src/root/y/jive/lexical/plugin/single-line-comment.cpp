
#include "y/jive/lexical/plugin/single-line-comment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            SingleLineComment:: ~SingleLineComment() noexcept
            {
            }


            void SingleLineComment:: setup()
            {
                drop("dot",".");
                back("[:endl:]",true);
            }
        }

    }

}
