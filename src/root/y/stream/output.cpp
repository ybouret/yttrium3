
#include "y/stream/output.hpp"

namespace Yttrium
{

    OutputStream:: OutputStream() : Stream()
    {
        
    }

    OutputStream:: ~OutputStream() noexcept
    {

    }

    size_t OutputStream:: emit(const uint8_t &x)
    {
        write( (char)x );
        return 1;
    }


    size_t OutputStream:: emit(const uint16_t &x)
    {
        const uint8_t u[2] = { (uint8_t)x, (uint8_t)(x>>8) };
        write(u,Y_Static_Size(u));
        return Y_Static_Size(u);
    }

    size_t OutputStream:: emit(const uint32_t &x)
    {
        const uint8_t u[4] =
        {
            (uint8_t)x,
            (uint8_t)(x>>8),
            (uint8_t)(x>>16),
            (uint8_t)(x>>24)
        };
        write(u,Y_Static_Size(u));
        return Y_Static_Size(u);
    }

    size_t OutputStream:: emit(const uint64_t &x)
    {
        const uint8_t u[8] =
        {
            (uint8_t)x,
            (uint8_t)(x>>8),
            (uint8_t)(x>>16),
            (uint8_t)(x>>24),
            (uint8_t)(x>>32),
            (uint8_t)(x>>40),
            (uint8_t)(x>>48),
            (uint8_t)(x>>56)
        };
        write(u,Y_Static_Size(u));
        return Y_Static_Size(u);
    }





}

#include "y/stream/io/encode64.hpp"

namespace Yttrium
{
    size_t OutputStream:: vbr64(const uint64_t qw)
    {
        const IO::Encode64 enc(qw); assert(enc.length()>0);
        const size_t blockSize = enc.length();
        write(enc.ro(),blockSize);
        return blockSize;
    }

}
