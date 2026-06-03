#include "y/jive/syntax/outcome.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Outcome:: ~Outcome() noexcept
            {
            }

            Outcome:: Outcome(const Result _result,
                              const Sanity _sanity,
                              const Status _status) noexcept :
            result(_result),
            sanity(_sanity),
            status(_status)
            {

            }

            Outcome:: Outcome(const Outcome &_) noexcept :
            result(_.result),
            sanity(_.sanity),
            status(_.status)
            {
            }

        }
        
    }

}

