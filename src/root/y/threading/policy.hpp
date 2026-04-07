
//! \file

#ifndef Y_Threading_Policy_Included
#define Y_Threading_Policy_Included 1

#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Threading
    {
        class Policy : public Lockable
        {
        protected:
            explicit Policy() noexcept;
            virtual ~Policy() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Policy);
        };
    }

}

#endif // !Y_Threading_Policy_Included

