//! \file

#ifndef Y_Core_HSort_Included
#define Y_Core_HSort_Included 1

#include "y/type/sign.hpp"
#include "y/libc/sort.h"
#include "y/memory/zombie.hpp"

namespace Yttrium
{
    namespace Core
    {
        struct HSort
        {
            template <typename T, typename COMPARE> static inline
            int CompareWrapper(const void * const lhs, const void * const rhs, void * const args) noexcept
            {
                assert(0!=lhs);
                assert(0!=rhs);
                assert(0!=args);
                COMPARE &compare = *(COMPARE *)args;
                const T &L       = *static_cast<const T *>(lhs);
                const T &R       = *static_cast<const T *>(rhs);
                return (int) compare(L,R);
            }

            //!
            /**
             calling a C function,compare must not throw
             */
            template <typename T, typename COMPARE> static inline
            void Make(T arr[], const size_t num, COMPARE &compare) noexcept
            {
                static YttriumCompare fcn = CompareWrapper<T,COMPARE>;
                Memory::Zombie<T>     rra;
                Yttrium_Sort(arr,num,sizeof(T),fcn,(void*)&compare,rra());
            }

            template <typename T> static inline
            void Increasing(T arr[], const size_t num) noexcept
            {
                Make(arr,num,Sign::Increasing<T>);
            }


            template <typename T> static inline
            void Decreasing(T arr[], const size_t num) noexcept
            {
                Make(arr,num,Sign::Decreasing<T>);
            }

        };


    }
}

#endif // !Y_Core_HSort_Included

