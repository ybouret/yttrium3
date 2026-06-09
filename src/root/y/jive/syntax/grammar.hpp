
//! \file

#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/grammar/core.hpp"
#include "y/jive/syntax/rule/all.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Parser;

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
                typedef Syntax::Aggregate     Aggregate; //!< echo
                typedef Syntax::Alternate     Alternate; //!< echo
                typedef Syntax::XNode         XNode; //!< echo
                typedef Syntax::XList         XList; //!< echo



                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param gid language name \param prs optional parent parser
                template <typename ID> inline
                explicit  Grammar(const ID &     gid,
                                  Parser * const prs) :
                CoreGrammar(gid),
                parser(prs)
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
                const Terminal & trm(const ID & ruleName,
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
                    return add( new Alternate(ruleName,parser) );
                }

              


                //! create entitled aggregate \param ruleName name \return added aggregate
                template <typename ID> inline
                Aggregate & agg(const ID & ruleName)
                {
                    return add( new Aggregate(ruleName,Entitled,parser) );
                }

                //! create grouping aggregate \param ruleName name \return added aggregate
                template <typename ID> inline
                Aggregate & grp(const ID & ruleName)
                {
                    return add( new Aggregate(ruleName,Grouping,parser) );
                }

                //! create yielding aggregate \param ruleName name \return added aggregate
                template <typename ID> inline
                Aggregate & yld(const ID & ruleName)
                {
                    return add( new Aggregate(ruleName,Yielding,parser) );
                }



                const Rule & pick(const Rule &, const Rule &);               //!< \return alternate of rules
                const Rule & pick(const Rule &, const Rule &, const Rule &); //!< \return alternate of rules
                const Rule & cat(const Rule &, const Rule &);                //!< \return grouping of rules
                const Rule & cat(const Rule &, const Rule &, const Rule &);  //!< \return grouping of rules

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! validate rules and freeze
                void validate();

                const Rule * querySyntaxRule(const String &) const noexcept; //!< \return found syntax rule

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Parser * const parser; //!< optional parent parser

            private:
                Y_Disable_Copy_And_Assign(Grammar); //!< discarded

            };
        }

    }

}

#endif // !Y_Jive_Syntax_Grammar_Included

