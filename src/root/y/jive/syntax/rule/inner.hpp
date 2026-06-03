
//! \file

#ifndef Y_Jive_Syntax_Inner_Included
#define Y_Jive_Syntax_Inner_Included 1

#include "y/jive/syntax/rule/internal.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            //__________________________________________________________________
            //
            //
            //
            //! Dummy internal rule, to test
            //
            //
            //__________________________________________________________________
            class Inner : public Internal
            {
            public:
                static const uint32_t UUID = Y_FOURCC('I','N','N','R'); //!< alias
                explicit Inner();                                       //!< setup
                virtual ~Inner() noexcept;                              //!< cleanup

                virtual const char *   vizShape()     const noexcept;
                virtual const char *   vizStyle()     const noexcept;
                Y_Jive_Syntax_Rule_Decl(); //!< accepts

            private:
                Y_Disable_Copy_And_Assign(Inner);                       //!< discarded
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Inner_Included

