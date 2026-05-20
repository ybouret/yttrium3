

//! \file

#ifndef Y_Jive_Lexical_Plugin_Included
#define Y_Jive_Lexical_Plugin_Included 1

#include "y/jive/lexical/scanner.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Lexer;

        namespace Lexical
        {
           
            class Plugin : public Scanner
            {
            public:

                template <typename ID, typename RX> inline
                explicit Plugin(const ID &   id,
                                const RX &   rx,
                                Lexer    &   lxr,
                                const OnEOS  eos) :
                Scanner(id,eos),
                spark( RegExp::Compile(rx,0) ),
                lexer( lxr )
                {
                }

                virtual ~Plugin() noexcept;

                virtual void enter();
                virtual void leave();

                const Motif spark;
                Lexer      &lexer;
                
            private:
                Y_Disable_Copy_And_Assign(Plugin);

            };

        }

    }

}

#endif // !Y_Jive_Lexical_Plugin_Included

