
//! \file

#ifndef Y_Jive_Lexical_JString_Included
#define Y_Jive_Lexical_JString_Included 1

#include "y/jive/lexical/plugin/string.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            class JString : public String_
            {
            public:
                static const char Mark = '\"';

                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit JString(const PID & pid,
                                 Stack     & stk) :
                String_(pid,stk,Mark,Mark)
                {
                    init();
                }

                //! cleanup
                virtual ~JString() noexcept;
            private:
                Y_Disable_Copy_And_Assign(JString);
                void init(); //!< register quote, langle and rangle
            };

        }

    }

}

#endif // !Y_Jive_Lexical_JString_Included

