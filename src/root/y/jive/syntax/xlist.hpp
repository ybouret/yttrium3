
//! \file

#ifndef Y_Jive_Syntax_XList_Included
#define Y_Jive_Syntax_XList_Included 1

#include "y/jive/lexical/stack.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class XNode;

            class XList : public CxxListOf<XNode>
            {
            public:
                explicit XList() noexcept;
                virtual ~XList() noexcept;

                void     returnTo(Lexical::Stack &) noexcept;

            private:
                Y_Disable_Copy_And_Assign(XList);
            };

        }

    }

}

#endif // !Y_Jive_Syntax_XList_Included

