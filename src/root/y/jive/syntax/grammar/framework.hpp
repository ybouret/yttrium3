
//! \file

#ifndef Y_Jive_Syntax_Framework_Included
#define Y_Jive_Syntax_Framework_Included 1

#include "y/pointer/auto.hpp"

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
                Framework(Lexer &,Source &) noexcept;
                ~Framework() noexcept;

                Lexical::Unit * get();
                void            put(Lexical::Unit *) noexcept;
                void            grow(XNode * const)  noexcept;

                AutoPtr<XNode> xtree;
                Lexer  &       lexer;
                Source &       source;
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

