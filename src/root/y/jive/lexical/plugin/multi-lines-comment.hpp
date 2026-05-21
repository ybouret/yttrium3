

//! \file

#ifndef Y_Jive_Multi_Lines_Comment_Included
#define Y_Jive_Mutli_Lines_Comment_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class MultiLinesComment : public Plugin
            {
            public:
                template <typename ID, typename INI, typename END>
                explicit MultiLinesComment(const ID  & id,
                                           const INI & ini,
                                           const END & end,
                                           Lexer     & lxr) :
                Plugin(id,ini,lxr)
                {
                    (void) back(end);
                    setup();
                }

                virtual ~MultiLinesComment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(MultiLinesComment);
                void setup();


            };
        }

    }

}

#endif // !Y_Jive_Multi_Lines_Comment_Included

