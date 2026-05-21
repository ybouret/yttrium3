

//! \file

#ifndef Y_Jive_Lexical_Plugin_Included
#define Y_Jive_Lexical_Plugin_Included 1

#include "y/jive/lexical/scanner.hpp"

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
                spark( RegExp::Compile(rx,0) )
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
                virtual void enter(); //!< invoked on enter
                virtual void leave(); //!< invoked on leave, possibility to modify lexer

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                const Motif spark; //!< compile pattern that call the plugin

            private:
                Y_Disable_Copy_And_Assign(Plugin); //!< discarded

            };

        }

    }

}

#endif // !Y_Jive_Lexical_Plugin_Included

