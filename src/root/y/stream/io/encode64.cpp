#include "y/stream/io/encode64.hpp"
#include "y/calculus/required-bits.hpp"
#include "y/libc/block/zero.h"

#include <cstring>
#include <iostream>

namespace Yttrium
{
    namespace IO
    {

        Encode64:: ~Encode64() noexcept
        {
            Y_BZero(wksp);
        }

        Encode64:: Encode64(uint64_t data) noexcept :
        nOut(0),
        byte(0),
        wksp()
        {
            Coerce(byte) = (uint8_t *) Y_BZero(wksp);

            const size_t dataBits = RequiredBitsFor(data);
            const size_t fullBits = HeaderBits + dataBits;
            const size_t numBytes = Alignment::On<8>::Ceil(fullBits) >> 3; assert(numBytes>0);
            const size_t numExtra = numBytes - 1;
            assert(numExtra<=Size);
            assert( RequiredBitsFor(numExtra) <= HeaderBits);

            // write header
            nOut     = 1+numExtra;
            byte[0]  = ((uint8_t) numExtra) << SourceBits;

            // write SourceBits of qw
            byte[0] |= (uint8_t)(data&SourceMask);

            if(dataBits<=SourceBits)
            {
                assert(1==nOut);
                return;
            }

            // write extra bits
            data    >>= SourceBits;
            for(size_t i=1;i<=numExtra;++i)
            {
                byte[i] = (uint8_t) data;
                data >>= 8;
            }


        }

        const void * Encode64:: ro() const noexcept
        {
            return byte;
        }

        size_t Encode64:: length() const noexcept
        {
            return nOut;
        }

    }
}
