
//! \file

#ifndef Y_Core_Rand_Included
#define Y_Core_Rand_Included 1

#include "y/config/setup.hpp"
#include <cassert>
#include <cmath>

namespace Yttrium
{
    namespace Core
    {
        class Rand
        {
        public:
            explicit Rand(const long init=-1) noexcept;
            virtual ~Rand() noexcept;

            float operator()() noexcept;

            template <typename T> inline
            T leq(const T n) noexcept
            {
                return (T) floorf( (float)n * (*this)() + 0.5f);
            }

            template <typename T> inline
            T in(const T lower, const T upper) noexcept
            {
                assert(upper>=lower);
                return lower + leq<T>(upper-lower);
            }




        private:
            Y_Disable_Copy_And_Assign(Rand);
            long seed;
        };
    }

}

#endif // !Y_Core_Rand_Included

