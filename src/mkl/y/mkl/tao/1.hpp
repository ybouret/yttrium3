//! \file

#ifndef Y_MKL_Tao1_Included
#define Y_MKL_Tao1_Included 1

#include "y/mkl/api/adaptor.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Tao
        {

            //! load a range into another one
            /**
             \param tgt initial target iterator
             \param num number of items to load
             \param src initial source iterator
             */
            template <typename TGT_ITER, typename SRC_ITER> inline
            void VLoad(TGT_ITER tgt, size_t num, SRC_ITER src)
            {
                while(num-- > 0)
                    **(tgt++) = *(src++);
            }

            //! load a sequence into another one
            /**
             \param target target sequence
             \param source source sequence (larger than target)
             */
            template <typename TARGET, typename SOURCE> inline
            void VLoad(TARGET &target, SOURCE &source)
            {
                assert(source.size()>=target.size());
                VLoad(target.begin(),target.size(),source.begin());
            }

            //! save a sequence into another one
            /**
             \param target target sequence (larger than source)
             \param source source sequence
             */
            template <typename TARGET, typename SOURCE> inline
            void VSave(TARGET &target, SOURCE &source)
            {
                assert(target.size()>=source.size());
                VLoad(target.begin(),target.size(),source.begin());
            }
        }

        namespace Tao
        {

            //! append a range to another one
            /**
             \param tgt initial target iterator
             \param num number of items to load
             \param src initial source iterator
             */
            template <typename TGT_ITER, typename SRC_ITER> inline
            void VAdd(TGT_ITER tgt, size_t num, SRC_ITER src)
            {
                while(num-- > 0)
                    **(tgt++) += *(src++);
            }

            //! append a sequence to another one
            /**
             \param target target sequence
             \param source source sequence (larger than target)
             */
            template <typename TARGET, typename SOURCE> inline
            void VAdd(TARGET &target, SOURCE &source)
            {
                assert(source.size()>=target.size());
                VAdd(target.begin(),target.size(),source.begin());
            }

        }


        namespace Tao
        {
            template <typename TGT_ITER, typename T, typename SRC_ITER> inline
            void VAdd(TGT_ITER tgt, size_t n, T &factor, SRC_ITER src)
            {
                static const TypeToType<T> Type = {};
                while(n-- > 0)
                {
                    const T arg = factor * AdaptedTo(Type,*(src++));
                    *(tgt++) = arg;
                }
            }

            template <typename TARGET, typename SOURCE> inline
            void VAdd(TARGET &target, typename TARGET::ParamType factor, SOURCE &source)
            {
                assert(source.size()>=target.size());
                VAdd(target.begin(),target.size(),factor,source.begin());
            }

        }

    }

}

#endif // !Y_MKL_Tao1_Included
