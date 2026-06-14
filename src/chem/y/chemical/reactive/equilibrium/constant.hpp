

//! \file

#ifndef Y_Chemical_ConstantEquilibrium_Included
#define Y_Chemical_ConstantEquilibrium_Included 1

#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class ConstantEquilibrium : public Equilibrium
        {
        public:
            explicit ConstantEquilibrium(const String &, const size_t, const xreal_t);
            virtual ~ConstantEquilibrium() noexcept;


        private:
            Y_Disable_Copy_And_Assign(ConstantEquilibrium);
            virtual xreal_t getK(xreal_t);
            const xreal_t K_;
        };

    }

}

#endif // !Y_Chemical_ConstantEquilibrium_Included

