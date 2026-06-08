
//! \file

#ifndef Y_Jive_Lexical_Verbatim_Included
#define Y_Jive_Lexical_Verbatim_Included 1

#include "y/jive/lexical/plugin/advanced.hpp"

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
            //! Advanced Plugin example: extract all between Expression
            //
            //
            //__________________________________________________________________
            class Verbatim : public AdvancedPlugin
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________

                static const char * const Expression; //!< "\verb"

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit Verbatim(const PID & pid,
                                  Stack     & stk) :
                AdvancedPlugin(pid,Expression,stk,RejectEOS),
                spot(name),
                data()
                {
                    initialize();
                }


                //! cleanup
                virtual ~Verbatim() noexcept;

            private:
                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Spot  spot; //!< origin spot
                Token data; //!< current data

                Y_Disable_Copy_And_Assign(Verbatim); //!< dicarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                void         initialize();
                void         onChar(Token &) noexcept;
#endif

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void enter(Token&) noexcept;
                virtual void leave(Token&) noexcept;
                
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Verbatim_Included

