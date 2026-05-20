
//! \file

#ifndef Y_Jive_Single_Line_Comment_Included
#define Y_Jive_Single_Line_Comment_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class SingleLineComment : public Plugin
            {
            public:
                template <typename ID, typename RX>
                explicit SingleLineComment(const ID & id,
                                           const RX & rx,
                                           Lexer    & lxr) :
                Plugin(id,rx,lxr)
                {
                    setup();
                }
                
                virtual ~SingleLineComment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(SingleLineComment);
                void setup();
                

            };
        }

    }

}

#endif // !Y_Jive_Single_Line_Comment_Included

