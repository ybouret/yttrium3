
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

                //! setup emtpy
                /**
                 \param ruleName name
                 \param myParser parent parser if present
                 */
                template <typename ID> inline
                explicit Alternate(const ID &     ruleName,
                                   Parser * const myParser) :
                Compound(ruleName,UUID,myParser)
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
                virtual const char *   vizShape()     const noexcept;
                virtual const char *   vizStyle()     const noexcept;
                Y_Jive_Syntax_Rule_Decl(); //!< accepts


            private:
                Y_Disable_Copy_And_Assign(Alternate); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Alternate_Included

