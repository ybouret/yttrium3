
//! \file

#ifndef Y_Jive_Syntax_Aggregate_Included
#define Y_Jive_Syntax_Aggregate_Included 1

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
            //! Aggregate of rules
            //
            //
            //__________________________________________________________________
            class Aggregate : public Compound
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A','G','G','_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup emtpy \param ruleName name
                template <typename ID> inline
                explicit Aggregate(const ID &ruleName) :
                Compound(ruleName,UUID)
                {

                }

                //! cleanup
                virtual ~Aggregate() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizSelf(OutputStream &) const;
                Y_Jive_Syntax_Rule_Decl();


            private:
                Y_Disable_Copy_And_Assign(Aggregate); //!< discarded
            };

        }

    }
}

#endif // !Y_Jive_Syntax_Aggregate_Included

