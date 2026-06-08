
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/defs.hpp"
#include "y/stream/identifier.hpp"
#include "y/graphviz/vizible.hpp"
#include "y/jive/syntax/grammar/framework.hpp"
#include "y/jive/syntax/outcome.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Lexer;
        class Source;
        
        namespace Syntax
        {
            class XNode;
            
#define Y_Jive_Syntax_Rule_Decl() virtual Outcome       accepts(Framework &) const          //!< declaration   prolog
#define Y_Jive_Syntax_Rule_Impl(CLS)      Outcome CLS:: accepts(Framework &framework) const //!< implementatin prolog


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
                // Definitions
                //
                //______________________________________________________________
                static bool Verbose; //!< verbosity flag

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
                Y_Jive_Syntax_Rule_Decl() = 0;                            //!< accepts(...)
                virtual OutputStream & vizLink(OutputStream &) const;     //!< emit graphviz code for links         \return output stream
                virtual const char *   vizShape()     const noexcept = 0; //!< \return shape for GraphViz
                virtual const char *   vizStyle()     const noexcept = 0; //!< \return style for GraphViz

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                OutputStream & vizSelf(OutputStream &)      const; //!< emit graphviz code for this, no link \return output stream
                OutputStream & vizPpty(OutputStream &)      const; //!< emit shape and stype \return output stream
                const char *   humanReadableKind() const noexcept; //!< \return human readable kind
                bool           isInternal()        const noexcept; //!< \return true iff internal
                bool           isTerminal()        const noexcept; //!< \return true iff terminal
                

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
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

