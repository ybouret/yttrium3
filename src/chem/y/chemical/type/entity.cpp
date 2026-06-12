
#include "y/chemical/type/entity.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Entity:: Entity() : name() {}

        Entity:: ~Entity() noexcept
        {
        }

        Entity:: Entity(const String &_) : name(_) {}

        const String & Entity:: key() const noexcept
        {
            return name;
        }
    }

}


