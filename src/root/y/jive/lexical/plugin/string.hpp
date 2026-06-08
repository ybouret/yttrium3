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
            class String_ : public AdvancedPlugin
            {
            public:
                //! setup
                /**
                 \param pid plugin name
                 \param stk lexer stack
                 */
                template <typename PID> inline
                explicit String_(const PID & pid,
                                Stack     & stk,
                                const char  ini,
                                const char  end) :
                AdvancedPlugin(pid,ini,stk,RejectEOS),
                spot(name),
                data()
                {
                    initialize(ini,end);
                }

                virtual ~String_() noexcept;

                //! \return ASCCI but quote, dquotes, backslash, langle and rangle
                static Leading GetCore() noexcept;

            protected:
                Spot  spot;
                Token data;

                void doChar(const char);

            private:
                Y_Disable_Copy_And_Assign(String_);
                void initialize(const char ini, const char end);
                void onCore(Token &) noexcept;
                void onChar(Token &) noexcept;
                void onEscMark(Token &) noexcept;
                void doEscMark(const char);



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

