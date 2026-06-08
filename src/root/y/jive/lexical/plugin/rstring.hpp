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
            //__________________________________________________________________
            //
            //
            //
            //! Raw string
            //
            //
            //__________________________________________________________________
            class RString : public String_
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char         Mark = '\''; //!< alias
                static const char * const XEsc;        //!< register dquotes, langle and rangle

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit RString(const PID & pid,
                                 Stack     & stk) :
                String_(pid,stk,Mark,Mark,XEsc)
                {
                }

                //! cleanup
                virtual ~RString() noexcept;

            private:
                Y_Disable_Copy_And_Assign(RString); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Lexical_RString_Included
