
#include "y/information/stream/cipher.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Information
    {
        StreamCipher:: ~StreamCipher() noexcept
        {
        }

        StreamCipher::  StreamCipher() noexcept : Serializable()
        {
        }


        void StreamCipher:: transform(void * const target, const void * const source, size_t length) noexcept
        {
            assert(!(0==target&&length>0) );
            assert(!(0==source&&length>0) );

            uint8_t *       tgt = static_cast<uint8_t *>(target);
            const uint8_t * src = static_cast<const uint8_t *>(source);

            StreamCipher &self = *this;
            while(length-- > 0)
            {
                *(tgt++) = self( *(src++) );
            }

        }

    }
}
