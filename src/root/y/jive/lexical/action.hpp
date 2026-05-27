

//! \file

#ifndef Y_Jive_Lexical_Action_Included
#define Y_Jive_Lexical_Action_Included 1

#include "y/functor.hpp"
#include "y/pointer/easy.hpp"
#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            typedef Functor<void,TL1(Token)> ActionType;

            class Action : public ActionType, public Counted
            {
            public:
                template <typename OBJECT_POINTER, typename METHOD_POINTER> inline
                explicit Action(OBJECT_POINTER * const objectPointer, METHOD_POINTER const methodPointer) :
                ActionType(objectPointer,methodPointer)
                {
                }

                virtual ~Action() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Action);
            };

            typedef EasyPtr<Action> RuleHook;

        }
    }
}

#endif // !Y_Jive_Lexical_Action_Included
