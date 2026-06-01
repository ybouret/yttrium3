

//! \file

#ifndef Y_Jive_Lexical_Plugin_Included
#define Y_Jive_Lexical_Plugin_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/jive/lexical/stack.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {


            //__________________________________________________________________
            //
            //
            //
            //! Plugin interface
            //
            //
            //__________________________________________________________________
            class Plugin : public Scanner
            {
            public:
                //! setup
                /**
                 \param id  name
                 \param rx  regular expression triggering call
                 \param lxr parent lexer
                 \param eos End Of Stream policy
                 */
                template <typename ID, typename RX> inline
                explicit Plugin(const ID &   id,
                                const RX &   rx,
                                const OnEOS  eos) :
                Scanner(id,eos),
                expr( rx )
                {
                }

                //! cleanup
                virtual ~Plugin() noexcept;

                

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                const String expr; //!< expression that triggers the call to the plugin

            private:
                Y_Disable_Copy_And_Assign(Plugin); //!< discarded

            };

        }

    }

}

#endif // !Y_Jive_Lexical_Plugin_Included

