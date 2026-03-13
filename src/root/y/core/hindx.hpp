
//! \file

#ifndef Y_Core_HIndx_Included
#define Y_Core_HIndx_Included 1

#include "y/type/sign.hpp"
#include "y/libc/sort.h"
#include "y/memory/zombie.hpp"

namespace Yttrium
{
    namespace Core
    {
        //! Index for C-style arrays
        struct HIndx
        {

            //! parameters for CompareWrapper
            template <typename T, typename COMPARE>
            struct Parameters
            {
                T       * arr; //!< original array
                COMPARE & cmp; //!< element-wise comparison
            };

            //! wrapper as YttriumCompare prototype
            /**
             \param lhs lhs pointer
             \param rhs rhs pointer
             \param args arguments
             \return wrapped comparison
             */
            template <typename T, typename COMPARE> static inline
            int CompareWrapper(const void * const lhs, const void * const rhs, void * const args) noexcept
            {
                assert(0!=lhs);
                assert(0!=rhs);
                assert(0!=args);
                Parameters<T,COMPARE> &params = *static_cast< Parameters<T,COMPARE> *>( args );
                const size_t i = *static_cast<const size_t *>(lhs);
                const size_t j = *static_cast<const size_t *>(rhs);
                return params.cmp(params.arr[i],params.arr[j]);

            }

            //! sort according to comparison
            /**
             \param idx array [0:num-1]
             \param arr array [0:num-1]
             \param num number of items
             \param compare valid comparator
             */
            template <typename T, typename COMPARE> static inline
            void Make(size_t idx[], T arr[], const size_t num, COMPARE &compare) noexcept
            {
                static YttriumCompare  fcn = CompareWrapper<T,COMPARE>;
                Parameters<T,COMPARE>  arg = { arr, compare };
                Memory::Zombie<size_t> rra;
                for(size_t i=0;i<num;++i) idx[i] = i;
                Yttrium_Sort(idx,num,sizeof(size_t),fcn,&arg,rra());
            }

            //! indexing by default increasing order
            /**
             \param idx array [0:num-1]
             \param arr array [0:num-1]
             \param num number of items
             */
            template <typename T> static inline
            void Increasing(size_t idx[], T arr[], const size_t num) noexcept
            {
                Make(idx,arr,num,Sign::Increasing<T>);
            }

            //! indexing by default decreasing order
            /**
             \param idx array [0:num-1]
             \param arr array [0:num-1]
             \param num number of items
             */
            template <typename T> static inline
            void Decreasing(size_t idx[], T arr[], const size_t num) noexcept
            {
                Make(idx,arr,num,Sign::Decreasing<T>);
            }

        };


    }
}

#endif // !Y_Core_HIndx_Included

