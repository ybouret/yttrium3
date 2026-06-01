
//! \file

#ifndef Y_Jive_Syntax_Alternate_Included
#define Y_Jive_Syntax_Alternate_Included 1

#include "y/jive/syntax/rule/compound.hpp"
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
            //! Alternate rules
            //
            //
            //__________________________________________________________________
            class Alternate : public Compound
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A','L','T','_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup emtpy \param ruleName name
                template <typename ID> inline
                explicit Alternate(const ID &ruleName) :
                Compound(ruleName,UUID)
                {

                }

                //! cleanup
                virtual ~Alternate() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizSelf(OutputStream &) const;


            private:
                Y_Disable_Copy_And_Assign(Alternate); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Alternate_Included

