
//! \file

#ifndef Y_Jive_Syntax_Framework_Included
#define Y_Jive_Syntax_Framework_Included 1

#include "y/pointer/auto.hpp"
#include "y/type/replicate.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Lexer;
        class Source;
        namespace Lexical { class Unit; }

        namespace Syntax
        {
            class XNode;

            class Framework
            {
            public:
                Framework(Lexer &,Source &)                      noexcept;
                ~Framework()                                     noexcept;
                Framework(const Replicate_ &, const Framework &) noexcept; //!< replicate lexer,source,depth, NO xtree

                Lexical::Unit * get();
                void            put(Lexical::Unit *) noexcept;
                void            grow(XNode * const)  noexcept;
                void            join(Framework &)    noexcept;
                void            dump()               noexcept;
                XNode *         operator->()         noexcept;
                XNode *         pop()                noexcept; //!< \return xtree.yield(), checked
                XNode *         set(XNode * const)   noexcept;
                
            protected:
                AutoPtr<XNode> xtree;
                Lexer  &       lexer;
                Source &       source;
            public:
                const unsigned depth;

            private:
                Y_Disable_Copy_And_Assign(Framework);
            };

            class Nesting
            {
            public:
                Nesting(Framework &) noexcept;
                ~Nesting() noexcept;
            private:
                Y_Disable_Copy_And_Assign(Nesting);
                Framework &framework;
            };


        }

    }

}

#endif // !Y_Jive_Syntax_Framework_Included

