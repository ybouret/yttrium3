
#include "y/jive/lexical/scanner/code.hpp"
#include "y/exception.hpp"


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

            void Scanner:: add(Rule * const rule)
            {
                assert(rule);
                assert(code);

                code->add(rule);
            }


        }

    }

}

