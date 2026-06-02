

//! \file

#ifndef Y_Jive_Syntax_Repeat_Included
#define Y_Jive_Syntax_Repeat_Included 1

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
            //! Repeat
            //
            //
            //__________________________________________________________________
            class Repeat : public Wildcard
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('R','E','P','_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Repeat(const Rule &, const size_t); //!< setup with automatic naming
                virtual ~Repeat() noexcept;                  //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizSelf(OutputStream &) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t atLeast; //!< minimal count for succes

            private:
                Y_Disable_Copy_And_Assign(Repeat); //!< discarde
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Repeat_Included

