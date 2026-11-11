#include "y/apex/api/iterator.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"



using namespace Yttrium;

Y_UTEST(apex_iterator)
{
    {
        const uint8_t               data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
        Apex::ByteIterator<uint8_t> iter(data);
        for(size_t i=1;i<=8;++i)
        {
            const uint8_t byte = iter();
            Y_PRINTV( Hexadecimal(byte) );
        }
        std::cerr << std::endl;
    }

    {
        const uint16_t               data[4] = { 0x0201, 0x0403, 0x0605, 0x0807 };
        Apex::ByteIterator<uint16_t> iter(data);
        for(size_t i=1;i<=8;++i)
        {
            const uint8_t byte = iter();
            Y_PRINTV( Hexadecimal(byte) );
        }
        std::cerr << std::endl;
    }

    {
        const uint32_t               data[2] = { 0x04030201, 0x08070605 };
        Apex::ByteIterator<uint32_t> iter(data);
        for(size_t i=1;i<=8;++i)
        {
            const uint8_t byte = iter();
            Y_PRINTV( Hexadecimal(byte) );
        }
        std::cerr << std::endl;
    }


}
Y_UDONE()

