
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
                data()
                {
                    setup();
                }



                virtual ~Verbatim() noexcept;
            private:
                Y_Disable_Copy_And_Assign(Verbatim);
                void setup();
                void onChar(Token &);
                Token data;
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Verbatim_Included

