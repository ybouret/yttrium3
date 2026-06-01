
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

            class Verbatim : public AdvancedPlugin
            {
            public:
                static const char * const Expression;

                template <typename PID> inline
                explicit Verbatim(const PID & pid,
                                  Stack     & stk) :
                AdvancedPlugin(pid,Expression,stk,RejectEOS),
                spot(name),
                data()
                {
                    setup();
                }



                virtual ~Verbatim() noexcept;
            private:
                Spot  spot;
                Token data;

                Y_Disable_Copy_And_Assign(Verbatim);
                void setup();
                void onChar(Token &);
                virtual void enter(Token&) noexcept;
                virtual void leave(Token&) noexcept;
                
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Verbatim_Included

