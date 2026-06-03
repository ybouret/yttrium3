
//! \file

#ifndef Y_Jive_Syntax_CoreGrammar_Included
#define Y_Jive_Syntax_CoreGrammar_Included 1

#include "y/jive/syntax/rule.hpp"
#include "y/core/list/cxx.hpp"
#include "y/type/proxy.hpp"
#include "y/ability/freezable.hpp"

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
            class CoreGrammar :
            public Proxy< const Core::ListOf<Rule> >,
            public Freezable
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Syntax::Rule Rule; //!< echo

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
            protected:
                //! append \param rule \return added rule
                template <typename RULE>
                RULE & add( RULE * const rule)
                {
                    append(rule);
                    return *rule;
                }

            public:
                const Rule & topLevel()       const noexcept; //!< \return topLevel rule (rules.size>0)
                void         topLevel(const Rule &) noexcept; //!< set toplevel (existing) rule

                OutputStream & viz(OutputStream&) const;     //!< top-level graphviz code \return output stream
                void           render() const;               //!< render
                XNode *        run(Lexer &, Source &) const; 

                


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier lang; //!< lang identifier


            protected:
                CxxListOf<Rule> rules; //!< list of distinct rules, head is toplevel

            private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                Y_Disable_Copy_And_Assign(CoreGrammar);
                Y_Proxy_Decl();
                void append(Rule * const);
#endif
            };
        }

    }

}

#endif // !Y_Jive_Syntax_CoreGrammar_Included

