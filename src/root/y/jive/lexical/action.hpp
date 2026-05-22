
//! \file

#ifndef Y_Jive_Lexical_Action_Included
#define Y_Jive_Lexical_Action_Included 1

#include "y/jive/pattern.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            class Action : public Object
            {
            public:
                typedef Functor<void,TL1(Token)> Code;
                typedef CxxListOf<Action>        List;

                explicit Action(const Code &);
                virtual ~Action() noexcept;

#if 0
                template <typename OBJECT, typename METHOD>
                static inline Action * Create(Pattern * const p, OBJECT &host, METHOD meth)
                {
                    const Motif _form(p);
                    const Code  _code(&host,meth);
                    return new Action(_form,_code);
                }
#endif

                Code        code;
                Action *    next;
                Action *    prev;
            private:
                Y_Disable_Copy_And_Assign(Action);
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Action_Included

