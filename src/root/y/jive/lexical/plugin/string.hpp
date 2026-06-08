//! \file

#ifndef Y_Jive_Lexical_String_Included
#define Y_Jive_Lexical_String_Included 1

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
            //! Base class for strings in lexer
            //
            //
            //__________________________________________________________________
            class String_ : public AdvancedPlugin
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
                 \param pid plugin name
                 \param stk lexer stack
                 \param ini ini char
                 \param end end char
                 \param esc extra escaped char
                 */
                template <typename PID> inline
                explicit String_(const PID & pid,
                                 Stack     & stk,
                                 const char  ini,
                                 const char  end,
                                 const char * const esc) :
                AdvancedPlugin(pid,ini,stk,RejectEOS),
                spot(name),
                data()
                {
                    initialize(ini,end,esc);
                }

                //! cleanup
                virtual ~String_() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return vizible ASCII but quote, dquotes, backslash, langle and rangle
                static Leading GetCore() noexcept;

            protected:
                Spot  spot; //!< starting point
                Token data; //!< accumulator

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            private:
                Y_Disable_Copy_And_Assign(String_);
                void doChar(const char);
                void initialize(const char ini, const char end, const char * const esc);
                void onCore(Token &) noexcept;
                void onChar(Token &) noexcept;
                void onEscMark(Token &) noexcept;
                void doEscMark(const char);
                void onEscCntl(Token &);
                void onEscHexa(Token &) noexcept;
                void onEscExcp(Token &);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void enter(Token&) noexcept;
                virtual void leave(Token&);
            };
        }

    }

}

#endif // !Y_Jive_Lexical_String_Included

