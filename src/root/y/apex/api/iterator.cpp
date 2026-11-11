#include "y/apex/api/iterator.hpp"

namespace Yttrium
{
    namespace Apex
    {
        ByteIterator<uint8_t>:: ~ByteIterator() noexcept {}

        ByteIterator<uint8_t>:: ByteIterator(const uint8_t * const userEntry) noexcept :
        entry(userEntry)
        {
        }

        uint8_t ByteIterator<uint8_t>::  operator()(void) noexcept
        {
            return *(entry++);
        }

    }


    namespace Apex
    {
        ByteIterator<uint16_t>:: ~ByteIterator() noexcept {}

        ByteIterator<uint16_t>:: ByteIterator(const uint16_t * const userEntry) noexcept :
        entry(userEntry),
        word(*(entry++)),
        state(Return0)
        {
        }

        uint8_t ByteIterator<uint16_t>:: operator()(void) noexcept
        {
            switch(state)
            {
                case Return0: return get0();
                case Return1: return get1();
            }
            return 0;
        }

        uint8_t ByteIterator<uint16_t>:: get0() noexcept
        {
            const uint8_t byte = (uint8_t)word;
            word >>= 8;
            state = Return1;
            return byte;
        }


        uint8_t ByteIterator<uint16_t>:: get1() noexcept
        {
            const uint8_t byte = (uint8_t)word;
            word = *(entry++);
            state = Return0;
            return byte;
        }


    }

    namespace Apex
    {
        ByteIterator<uint32_t>:: ~ByteIterator() noexcept {}

        ByteIterator<uint32_t>:: ByteIterator(const uint32_t * const userEntry) noexcept :
        entry(userEntry),
        dword(*(entry++)),
        state(Return0)
        {
        }

        uint8_t ByteIterator<uint32_t>:: operator()(void) noexcept
        {
            switch(state)
            {
                case Return0: return get_(Return1);
                case Return1: return get_(Return2);
                case Return2: return get_(Return3);
                case Return3: return get3();
            }
            return 0;
        }


        uint8_t ByteIterator<uint32_t>:: get_(const State next) noexcept
        {
            const uint8_t byte = (uint8_t)dword;
            dword >>= 8;
            state = next;
            return byte;
        }


        uint8_t ByteIterator<uint32_t>:: get3() noexcept
        {
            const uint8_t byte = (uint8_t)dword;
            dword = *(entry++);
            state = Return0;
            return byte;
        }
    }

}

