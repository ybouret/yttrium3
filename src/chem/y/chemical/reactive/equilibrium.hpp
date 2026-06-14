
//! \file

#ifndef Y_Chemical_Equilibrium_Included
#define Y_Chemical_Equilibrium_Included 1

#include "y/chemical/reactive/components.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Equilibrium : public CountedObject, public Components
        {
        public:
            explicit Equilibrium(const String &, const size_t);
            virtual ~Equilibrium() noexcept;

            xreal_t K(xreal_t);

        private:
            Y_Disable_Copy_And_Assign(Equilibrium);
            virtual xreal_t getK(xreal_t) = 0;
        };

    }

}

#endif // !Y_Chemical_Equilibrium_Included

