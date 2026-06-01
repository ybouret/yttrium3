
//! \file

#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/rule.hpp"
#include "y/core/list/cxx.hpp"
#include "y/type/proxy.hpp"

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
            //! Grammar has a list of rules
            //
            //
            //__________________________________________________________________
            class Grammar : public Proxy< const Core::ListOf<Rule> >
            {
            public:
                typedef Syntax::Rule Rule;
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param id lang
                template <typename ID> inline
                explicit Grammar(const ID &id) :
                lang(id),
                rules()
                {
                }

                //! cleanup
                virtual ~Grammar() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                //! append \param rule \return added rule
                template <typename RULE>
                RULE & add( RULE * const rule)
                {
                    append(rule);
                    return *rule;
                }

                const Rule & topLevel()       const noexcept; //!< \return topLevel rule (rules.size>0)
                void         topLevel(const Rule &) noexcept; //!< set toplevel (existing) rule

                OutputStream & viz(OutputStream&) const;
                void           render() const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier lang; //!< lang identifier


            private:
                CxxListOf<Rule> rules; //!< list of distinct rules, head is toplevel

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                Y_Disable_Copy_And_Assign(Grammar);
                Y_Proxy_Decl();
                void append(Rule * const);
#endif
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Grammar_Included

