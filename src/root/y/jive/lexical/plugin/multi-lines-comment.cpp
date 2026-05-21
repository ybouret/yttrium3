

#include "y/jive/lexical/plugin/multi-lines-comment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            MultiLinesComment:: ~MultiLinesComment() noexcept
            {
            }


            void MultiLinesComment:: setup()
            {
                drop("dot",".");
                endl("endl","[:endl:]");
            }
        }

    }

}
