#include "y/stream/io/decode64.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/exception.hpp"
#include "y/calculus/required-bits.hpp"

namespace Yttrium
{
    namespace IO
    {

        bool Decode64:: ready() const noexcept
        {
            return expected <= 0;
        }

        std::ostream & operator<<(std::ostream &os, const Decode64 &d)
        {
            return os << Hexadecimal(d.value,Concise);
        }

        Decode64:: ~Decode64() noexcept
        {

        }


        const char * const Decode64::CallSign ="IO::Decode64";

        Decode64:: Decode64(const uint8_t b,
                            const char * const varName,
                            const char * const varPart) :
        value(0),
        numExtra(b),
        expected(0),
        dataBits(0)
        {
            // deduce num extra from HeaderBits
            Coerce(numExtra) >>= SourceBits;

            if(numExtra>Size)
            {
                Specific::Exception excp(CallSign,"too many extra bytes");
                throw excp.signedFor(varName,varPart);
            }

            // initialize
            Coerce(value)    = b;
            Coerce(value)   &= SourceMask;
            Coerce(expected) = numExtra;
            Coerce(dataBits) = SourceBits;
        }



        void Decode64:: operator()(const uint8_t      b,
                                   const char * const varName,
                                   const char * const varPart)
        {
            assert(expected>0);
            static const size_t MaxBits = Size * 8;
            const size_t        readBits = (expected<=1) ? RequiredBitsFor(b) : 8;

            if(dataBits+readBits>MaxBits)
            {
                Specific::Exception excp(CallSign,"too many bits");
                throw excp.signedFor(varName,varPart);
            }

            uint64_t qw = b;
            qw <<= dataBits;

            Coerce(value)    |= qw;
            Coerce(dataBits) += readBits;

            --Coerce(expected);
        }
    }

}


