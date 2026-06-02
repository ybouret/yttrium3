
//! \file

#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/core-grammar.hpp"
#include "y/jive/syntax/rule/all.hpp"

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
            //! Grammar is CoreGrammar + API
            //
            //
            //__________________________________________________________________
            class Grammar : public CoreGrammar
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Syntax::Aggregate Aggregate; //!< echo
                typedef Syntax::Alternate Alternate; //!< echo

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param id lang
                template <typename ID> inline
                explicit  Grammar(const ID &id) :
                CoreGrammar(id)
                {
                }

                //! cleanup
                virtual ~Grammar() noexcept;

                //______________________________________________________________
                //
                //
                // API
                //
                //______________________________________________________________

                //! register terminal
                /**
                 \param ruleName terminal name
                 \param ruleRole terminal role
                 \param ruleLoad terminal load
                 \return created terminal rule
                 */
                template <typename ID> inline
                const Rule & trm(const ID & ruleName,
                                 const Role ruleRole = Semantic,
                                 const Load ruleLoad = Standard)
                {
                    return add( new Terminal(ruleName,ruleRole,ruleLoad) );
                }

                const Rule & rep(const Rule &,const size_t); //!< \return repeat of source rule
                const Rule & opt(const Rule &);              //!< \return option source rule
                const Rule & zom(const Rule &);              //!< \return zero or more source rule
                const Rule & oom(const Rule &);              //!< \return one or more source rule

                //! create alternate \param ruleName name \return added alternate
                template <typename ID> inline
                Alternate & alt(const ID & ruleName)
                {
                    return add( new Alternate(ruleName) );
                }

                //! create aggregate \param ruleName name \return added aggregate
                template <typename ID> inline
                Aggregate & agg(const ID & ruleName)
                {
                    return add( new Aggregate(ruleName) );
                }

                void validate();


            private:
                Y_Disable_Copy_And_Assign(Grammar); //!< discarded

            };
        }

    }

}

#endif // !Y_Jive_Syntax_Grammar_Included

