
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
            //__________________________________________________________________
            //
            //
            //
            //! Option
            //
            //
            //__________________________________________________________________
            class Option : public Wildcard
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('O','P','T','_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Option(const Rule & );//!< setup with automatic naming
                virtual ~Option() noexcept;    //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizSelf(OutputStream &) const;
                Y_Jive_Syntax_Rule_Decl();

            private:
                Y_Disable_Copy_And_Assign(Option); //!< discarde
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Option_Included

