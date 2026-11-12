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
        word(0),
        state(Return0)
        {
        }

        uint8_t ByteIterator<uint16_t>:: operator()(void) noexcept
        {
            switch(state)
            {
                case Return0:
                    word = *(entry++);
                    state = Return1;
                    return (uint8_t)word;

                case Return1:
                    state = Return0;
                    return (uint8_t)(word>>=8);
            }
            //return 0;
        }

        


    }

    namespace Apex
    {
        ByteIterator<uint32_t>:: ~ByteIterator() noexcept {}

        ByteIterator<uint32_t>:: ByteIterator(const uint32_t * const userEntry) noexcept :
        entry(userEntry),
        dword(0),
        state(Return0)
        {
        }

        uint8_t ByteIterator<uint32_t>:: operator()(void) noexcept
        {
            switch(state)
            {
                case Return0:
                    dword = *(entry++);
                    state = Return1;
                    return (uint8_t)dword;

                case Return1:
                    state = Return2;
                    return (uint8_t)(dword >>= 8);

                case Return2:
                    state = Return3;
                    return (uint8_t)(dword >>= 8);

                case Return3:
                    state = Return0;
                    return (uint8_t)(dword >>= 8);
            }
            return 0;
        }



    }

}

