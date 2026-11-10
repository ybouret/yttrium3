#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Apex
    {

        template <typename T>
        class ByteIterator;

        template <>
        class ByteIterator<uint8_t>
        {
        public:

            inline ByteIterator(const uint8_t * const userEntry) noexcept :
            entry(userEntry)
            {
            }
            
            inline ~ByteIterator() noexcept {}

            inline uint8_t operator()(void) noexcept
            {
                return *(entry++);
            }


        private:
            Y_Disable_Copy_And_Assign(ByteIterator);
            const uint8_t * entry;
        };


        template <>
        class ByteIterator<uint16_t>
        {
        public:
            enum State
            {
                Return0,
                Return1
            };

            inline ByteIterator(const uint16_t * const userEntry) noexcept :
            entry(userEntry),
            word(*(entry++)),
            state(Return0)
            {
            }

            inline ~ByteIterator() noexcept {}

            inline uint8_t operator()(void) noexcept
            {
                switch(state)
                {
                    case Return0: return return0();
                    case Return1: return return1();
                }
                return 0;
            }


        private:
            Y_Disable_Copy_And_Assign(ByteIterator);
            const uint16_t * entry;
            uint16_t         word;
            State            state;

            inline uint8_t return0() noexcept
            {
                const uint8_t byte = (uint8_t)word;
                word >>= 8;
                state = Return1;
                return byte;
            }


            inline uint8_t return1() noexcept
            {
                const uint8_t byte = (uint8_t)word;
                word = *(entry++);
                state = Return0;
                return byte;
            }

        };

        template <>
        class ByteIterator<uint32_t>
        {
        public:
            enum State
            {
                Return0,
                Return1,
                Return2,
                Return3
            };

            inline ByteIterator(const uint32_t * const userEntry) noexcept :
            entry(userEntry),
            dword(*(entry++)),
            state(Return0)
            {
            }

            inline ~ByteIterator() noexcept {}

            inline uint8_t operator()(void) noexcept
            {
                switch(state)
                {
                    case Return0: return return0();
                    case Return1: return return1();
                    case Return2: return return2();
                    case Return3: return return3();
                }
                return 0;
            }


        private:
            Y_Disable_Copy_And_Assign(ByteIterator);
            const uint32_t * entry;
            uint32_t         dword;
            State            state;

            inline uint8_t return0() noexcept
            {
                const uint8_t byte = (uint8_t)dword;
                dword >>= 8;
                state = Return1;
                return byte;
            }

            inline uint8_t return1() noexcept
            {
                const uint8_t byte = (uint8_t)dword;
                dword >>= 8;
                state = Return2;
                return byte;
            }

            inline uint8_t return2() noexcept
            {
                const uint8_t byte = (uint8_t)dword;
                dword >>= 8;
                state = Return3;
                return byte;
            }


            inline uint8_t return3() noexcept
            {
                const uint8_t byte = (uint8_t)dword;
                dword = *(entry++);
                state = Return0;
                return byte;
            }

        };




    }
}

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

