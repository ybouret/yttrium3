
//! \file

#ifndef Y_Jive_Syntax_CoreGrammar_Included
#define Y_Jive_Syntax_CoreGrammar_Included 1

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
            //! Core Grammar has a list of rules
            //
            //
            //__________________________________________________________________
            class CoreGrammar : public Proxy< const Core::ListOf<Rule> >
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
                explicit CoreGrammar(const ID &id) :
                lang(id),
                rules()
                {
                }

                //! cleanup
                virtual ~CoreGrammar() noexcept;

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
                Y_Disable_Copy_And_Assign(CoreGrammar);
                Y_Proxy_Decl();
                void append(Rule * const);
#endif
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Grammar_Included

