
//! \file

#ifndef Y_Chemical_Actor_Included
#define Y_Chemical_Actor_Included 1

#include "y/chemical/species.hpp"
#include "y/chemical/type/defs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        enum Acting
        {
            AsSpec,
            AsConc
        };

        class Actor : public Object, public Entity
        {
        public:
            typedef CxxListOf<Actor> List;

            explicit Actor(const unsigned &, const Species &, const Acting);
            virtual ~Actor() noexcept;

            const unsigned nu;
            const Species &sp;
            Actor *        next;
            Actor *        prev;
            
        private:
            Y_Disable_Copy_And_Assign(Actor);
        };
    }

}

#endif // !Y_Chemical_Actor_Included
