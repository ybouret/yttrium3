
//! \file

#ifndef Y_Calculus_GC_Included
#define Y_Calculus_GC_Included 1

#include "y/type/is-signed-int.hpp"
#include "y/config/compiler.h"

namespace Yttrium
{

    namespace Calculus
    {
        //! 64-bits GC computation
        struct GC_
        {
            //! compute how much to keep
            /**
             \param size original size
             \param keep fraction to keep
             \return new size
             **/
            static uint64_t Kept(const uint64_t size, const uint8_t keep) noexcept;
        };

        template <typename T,bool> struct GC;

        //! alias, unsigned GC computation
        template <typename T>
        struct GC<T,false>
        {
            //! compute how much to keep
            /**
             \param size original unsigned size
             \param keep fraction to keep
             \return new size
             **/
            static inline T Kept(const T size, const uint8_t keep) noexcept
            {
                return (T) GC_::Kept(size,keep);
            }
        };

        //! alias, signed GC computation
        template <typename T>
        struct GC<T,true>
        {
            //! compute how much to keep
            /**
             \param size original signed size
             \param keep fraction to keep
             \return new size
             **/
            static inline T Kept(const T size, const uint8_t keep) noexcept
            {
                return size < 0 ? -(T) GC_::Kept(-size,keep) : (T) GC_::Kept(size,keep);
            }
        };
    }

    //! GC helper
    struct GC
    {
        //! compute how much to keep for any integer size
        /**
         \param size original size
         \param keep fraction to keep
         \return new size
         **/
        template <typename T> static inline
        T Kept(const T size, const uint8_t keep) noexcept
        {
            return Calculus::GC<T,IsSignedInt<T>::Value>::Kept(size,keep);
        }
    };

}

#endif // !Y_Calculus_GC_Included

