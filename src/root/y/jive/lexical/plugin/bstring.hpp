
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
            //__________________________________________________________________
            //
            //
            //
            //! Bracket string
            //
            //
            //__________________________________________________________________
            class BString : public String_
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char Ini = '<';    //!< alias
                static const char End = '>';    //!< alias
                static const char * const XEsc; //!< register quote and dquotes

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
                explicit BString(const PID & pid,
                                 Stack     & stk) :
                String_(pid,stk,Ini,End,XEsc)
                {
                }

                //! cleanup
                virtual ~BString() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(BString); //!< dicarded

            };

        }

    }

}

#endif // !Y_Jive_Lexical_BString_Included
