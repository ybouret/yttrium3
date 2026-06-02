
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/defs.hpp"
#include "y/stream/identifier.hpp"
#include "y/graphviz/vizible.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Lexer;
        class Source;
        
        namespace Syntax
        {
            class XNode;

            enum Outcome
            {
                Accepted, //!< accepted with new node
                Rejected, //!< rejected
                Weakened, //!< accepted with NO node
                Finished  //!< no more lexeme
            };

#define Y_Jive_Syntax_Rule_Decl() virtual Outcome       accepts(XNode * &, Lexer &, Source &) const
#define Y_Jive_Syntax_Rule_Impl(CLS)      Outcome CLS:: accepts(XNode * &tree, Lexer &lexer, Source &source) const


            //__________________________________________________________________
            //
            //
            //
            //! Rule base class
            //
            //
            //__________________________________________________________________
            class Rule : public Object, public Vizible
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
                 \param ruleKind kind
                 \param ruleUUID uuid
                 */
                template <typename RID> inline
                explicit Rule(const RID &    ruleName,
                              const Kind     ruleKind,
                              const uint32_t ruleUUID) :
                name(ruleName),
                kind(ruleKind),
                uuid(ruleUUID),
                next(0),
                prev(0)
                {
                }

                //! cleanup
                virtual ~Rule() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                Y_Jive_Syntax_Rule_Decl() = 0;
                virtual OutputStream & vizSelf(OutputStream &) const = 0; //!< emit graphviz code for this, no link \return output stream
                virtual OutputStream & vizLink(OutputStream &) const;     //!< emit graphviz code for links         \return output stream


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return human readable kind
                const char *   humanReadableKind() const noexcept;

                const Identifier name; //!< name
                const Kind       kind; //!< kind
                const uint32_t   uuid; //!< uuid
                Rule *           next; //!< for list
                Rule *           prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarded
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Rule_Included

