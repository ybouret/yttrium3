
//! \file

#ifndef Y_Jive_Lexical_BString_Included
#define Y_Jive_Lexical_BString_Included 1

#include "y/jive/lexical/plugin/string.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            class BString : public String_
            {
            public:
                static const char Ini = '<';
                static const char End = '>';

                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit BString(const PID & pid,
                                 Stack     & stk) :
                String_(pid,stk,Ini,End)
                {
                }

                //! cleanup
                virtual ~BString() noexcept;
            private:
                Y_Disable_Copy_And_Assign(BString);
                void init(); //!< register quote and dquotes

            };

        }

    }

}

#endif // !Y_Jive_Lexical_BString_Included
