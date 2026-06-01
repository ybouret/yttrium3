
//! \file

#ifndef Y_Jive_Syntax_Wildcard_Included
#define Y_Jive_Syntax_Wildcard_Included 1

#include "y/jive/syntax/rule/internal.hpp"

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
            //! Wildcard base class
            //
            //
            //__________________________________________________________________
            class Wildcard : public Internal
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param ruleName name
                 \param ruleUUID uuid
                 \param source   source rule
                 */
                template <typename ID>
                explicit Wildcard(const ID      & ruleName,
                                  const uint32_t  ruleUUID,
                                  const Rule    & source) :
                Internal(ruleName,ruleUUID),
                rule(source)
                {
                }


                //! cleanup
                virtual ~Wildcard() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizLink(OutputStream &) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Rule &rule; //!< source rule

            private:
                Y_Disable_Copy_And_Assign(Wildcard); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Wildcard_Included
