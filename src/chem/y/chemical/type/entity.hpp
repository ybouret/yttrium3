
//! \file

#ifndef Y_Chemical_Entity_Included
#define Y_Chemical_Entity_Included 1

#include "y/string.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Entity
        {
        public:
            explicit Entity();
            explicit Entity(const String &);
            virtual ~Entity() noexcept;

            const String & key() const noexcept;

            const String name;

        private:
            Y_Disable_Copy_And_Assign(Entity);
        };
    }

}

#endif // !Y_Chemical_Entity_Included
