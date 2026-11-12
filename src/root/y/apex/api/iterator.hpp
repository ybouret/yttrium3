//! \file

#ifndef Y_Apex_Iterator_Included
#define Y_Apex_Iterator_Included 1

#include "y/config/setup.hpp"

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

            ByteIterator(const uint8_t * const) noexcept;
            ~ByteIterator()                     noexcept;

            uint8_t operator()(void) noexcept;


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

            ByteIterator(const uint16_t * const) noexcept;
            ~ByteIterator()                      noexcept;

            uint8_t operator()(void) noexcept;

        private:
            Y_Disable_Copy_And_Assign(ByteIterator);
            const uint16_t * entry;
            uint16_t         word;
            State            state;
            
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

            ByteIterator(const uint32_t * const) noexcept;
            ~ByteIterator() noexcept;

            uint8_t operator()(void) noexcept;


        private:
            Y_Disable_Copy_And_Assign(ByteIterator);
            const uint32_t * entry;
            uint32_t         dword;
            State            state;
            
            uint8_t get_(const State) noexcept;
            uint8_t get3() noexcept;
        };




    }
}


#endif // !Y_Apex_Iterator_Included
