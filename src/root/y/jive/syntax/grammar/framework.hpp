
//! \file

#ifndef Y_Jive_Syntax_Framework_Included
#define Y_Jive_Syntax_Framework_Included 1

#include "y/pointer/auto.hpp"
#include "y/type/replicate.hpp"
#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Lexer;
        class Source;
        namespace Lexical { class Unit; }

        namespace Syntax
        {

            //__________________________________________________________________
            //
            //
            //
            //! Manage lexer, source and building tree for rules
            //
            //
            //__________________________________________________________________
            class Framework
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Framework(Lexer &,Source &)                      noexcept; //!< setup with empty tree, depth=1
                ~Framework()                                     noexcept; //!< cleanup
                Framework(const Replicate_ &, const Framework &) noexcept; //!< replicate lexer,source,depth, NO xtree

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Lexical::Unit * get();                         //!< use lexer and source \return next lexeme
                void            put(Lexical::Unit *) noexcept; //!< return unused lexeme
                void            grow(XNode * const)  noexcept; //!< XNode::Grow(xtree,xnode)
                void            join(Framework &)    noexcept; //!< XNode::Join(xtree,sub.xtree)
                void            dump()               noexcept; //!< return tree to lexer
                XNode *         operator->()         noexcept; //!< \return checked xtree content
                XNode *         pop()                noexcept; //!< \return xtree.yield(), checked
                XNode *         set(XNode * const)   noexcept; //!< \return xnode as new xtree

                std::ostream & indent(std::ostream&) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            protected:
                AutoPtr<XNode> xtree;  //!< current tree
                Lexer  &       lexer;  //!< lexer
                Source &       source; //!< source for lexer
            public:
                const unsigned depth; //!< current depth

            private:
                Y_Disable_Copy_And_Assign(Framework); //!< discarded
            };

            //__________________________________________________________________
            //
            //
            //
            //! Automatic nesting helper
            //
            //
            //__________________________________________________________________
            class Nesting
            {
            public:
                Nesting(Framework &) noexcept;      //!< increase framework depth
                ~Nesting()           noexcept;      //!< decrease framework depth
            private:
                Y_Disable_Copy_And_Assign(Nesting); //!< discarded
                Framework &framework;               //!< persistent host
            };

#define Y_Jive_Syntax(MSG) do { if(Jive::Syntax::Rule::Verbose) { framework.indent(std::cerr) << MSG << std::endl; } } while(false)

        }

    }

}

#endif // !Y_Jive_Syntax_Framework_Included

