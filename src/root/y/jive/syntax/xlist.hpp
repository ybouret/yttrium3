
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

            //__________________________________________________________________
            //
            //
            //
            //! XList for AST
            //
            //
            //__________________________________________________________________
            class XList : public CxxListOf<XNode>
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit XList() noexcept;
                virtual ~XList() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! return content to lexer
                void     returnTo(Lexical::Stack &) noexcept;

            private:
                Y_Disable_Copy_And_Assign(XList); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Syntax_XList_Included

