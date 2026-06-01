
//! \file

#ifndef Y_Jive_Syntax_Inner_Included
#define Y_Jive_Syntax_Inner_Included 1

#include "y/jive/syntax/rules/internal.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Inner : public Internal
            {
            public:
                static const uint32_t UUID = Y_FOURCC('I','N','N','R');
                explicit Inner();
                virtual ~Inner() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Inner);
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Inner_Included

