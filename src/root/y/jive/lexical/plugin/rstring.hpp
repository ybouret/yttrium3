//! \file

#ifndef Y_Jive_Lexical_RString_Included
#define Y_Jive_Lexical_RString_Included 1

#include "y/jive/lexical/plugin/string.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            class RString : public String_
            {
            public:
                static const char Mark = '\'';

                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit RString(const PID & pid,
                                 Stack     & stk) :
                String_(pid,stk,Mark,Mark)
                {
                    init();
                }

                //! cleanup
                virtual ~RString() noexcept;
            private:
                Y_Disable_Copy_And_Assign(RString);
                void init(); //!< register dquotes, langle and rangle
            };

        }

    }

}

#endif // !Y_Jive_Lexical_RString_Included
