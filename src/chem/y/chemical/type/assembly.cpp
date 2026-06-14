
#include "y/chemical/type/assembly.hpp"
#include "y/core/max.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Assembly:: ~Assembly() noexcept
        {
        }

        Assembly:: Assembly() noexcept : width(0)
        {
        }

        void Assembly:: enroll(const Entity &en) noexcept
        {
            InSituMax( Coerce(width), en.name.size() );
        }

        std::ostream & Assembly:: print(std::ostream &os, const Entity &en, const Justify::Type J) const
        {
            return os << Justify(en.name,width,J);
        }

        Assembly:: Assembly(const Assembly &_) noexcept :
        width(_.width)
        {
        }



    }
}

