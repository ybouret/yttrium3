
//! \file

#ifndef Y_Jive_Syntax_Option_Included
#define Y_Jive_Syntax_Option_Included 1

#include "y/jive/syntax/rule/wildcard.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Option : public Wildcard
            {
            public:
                static const uint32_t UUID = Y_FOURCC('O','P','T','_');

                explicit Option(const Rule &source);
                virtual ~Option() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Option);
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Option_Included

