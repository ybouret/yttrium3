#include "y/jive/lexical/scanner/code.hpp"


namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {


            Scanner:: ~Scanner() noexcept
            {
                assert(code);
                Destroy(code);
            }

            const Rule & Scanner:: add(Rule * const rule)
            {
                assert(rule);
                assert(code);
                code->add(rule);
                return *rule;
            }


            const Rule & Scanner:: processing(const Identifier &_name,
                                              const Motif &_form,
                                              const unsigned _deed)
            {
                return add( new Rule(_name,_form,_deed,_name) );
            }

        }

    }

}

