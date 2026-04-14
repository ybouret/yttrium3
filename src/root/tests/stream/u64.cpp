#include "y/stream/io/encode64.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"


namespace Yttrium {

    namespace IO
    {
        class Decode64 : public U64Bits
        {
        public:
            explicit Decode64(const uint8_t b, const char * const varName);
            virtual ~Decode64() noexcept;
            Y_OSTREAM_PROTO(Decode64);

            bool ready() const noexcept;
            void operator()(const uint8_t b, const char * const varName);

            const uint64_t value;
            const size_t   numExtra;
            const size_t   expected;
            const size_t   dataBits;
        private:
            Y_Disable_Copy_And_Assign(Decode64);
        };

        bool Decode64:: ready() const noexcept
        {
            return expected <= 0;
        }

        std::ostream & operator<<(std::ostream &os, const Decode64 &d)
        {
            return os << Hexadecimal(d.value,Concise);
        }

        Decode64:: Decode64(const uint8_t b, const char * const varName) :
        value(0),
        numExtra(b),
        expected(0),
        dataBits(0)
        {
            // deduce num extra from HeaderBits
            Coerce(numExtra) >>= SourceBits;

            if(numExtra>Size)
            {
                Specific::Exception excp("IO::Decode64","too many extra bytes");
                if(varName) excp.cat(" for %s", varName);
                throw excp;
            }

            // initialize
            Coerce(value)    = b;
            Coerce(value)   &= SourceMask;
            Coerce(expected) = numExtra;
            Coerce(dataBits) = SourceBits;
        }



        Decode64:: ~Decode64() noexcept
        {

        }

        void Decode64:: operator()(const uint8_t b, const char * const varName)
        {
            assert(expected>0);
            static const size_t MaxBits = Size * 8;
            const size_t readBits = (expected<=1) ? RequiredBitsFor(b) : 8;

            if(dataBits+readBits>MaxBits)
            {
                Specific::Exception excp("IO::Decode64","too many bits");
                if(varName) excp.cat(" for %s", varName);
                throw excp;
            }

            uint64_t qw = b;
            //std::cerr << "(read " << Hexadecimal(qw,Concise) << ")";
            qw <<= dataBits;

            Coerce(value)    |= qw;
            Coerce(dataBits) += readBits;


            --Coerce(expected);
        }

    }
}

using namespace Yttrium;


Y_UTEST(stream_u64)
{
    Core::Rand ran;

    Y_PRINTV(IO::U64Bits::Size);
    Y_PRINTV(IO::U64Bits::HeaderBits);
    Y_PRINTV(IO::U64Bits::SourceBits);
    Y_PRINTV(IO::U64Bits::SourceMask);
    

    for(size_t i=0;i<=64;++i)
    {
        for(size_t iter=0;iter<16;++iter)
        {
            const uint64_t qw = ran.gen<uint64_t>(i);
            IO::Encode64   enc64(qw);
            std::cerr << Hexadecimal(qw) << " => " << enc64;

            const uint8_t * u = (const uint8_t *)enc64.ro();
            IO::Decode64 dec64(u[0],0);
            Y_ASSERT(dec64.numExtra == enc64.length() -1 );

            //std::cerr << ":" << Hexadecimal(dec64.value,Concise);
            for(size_t i=1;i<enc64.length();++i)
            {
                dec64(u[i],0);
                //std::cerr << ":" << Hexadecimal(dec64.value,Concise);
            }
            std::cerr << " => " << dec64;
            std::cerr << std::endl;
            Y_ASSERT(dec64.value == qw);
        }
    }


}
Y_UDONE()

