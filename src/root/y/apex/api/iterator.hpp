//! \file

#ifndef Y_Apex_Iterator_Included
#define Y_Apex_Iterator_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {


        template <typename T> class ByteIterator;

        //______________________________________________________________________
        //
        //
        //
        //! Iterator on uint8_t array
        //
        //
        //______________________________________________________________________
        template <>
        class ByteIterator<uint8_t>
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            ByteIterator(const uint8_t * const) noexcept; //!< setup from user's data
            ~ByteIterator()                     noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return next byte, read only what is necessary
            uint8_t operator()(void) noexcept;

            //! \return true if cursor is within given memory area
            bool    within(const uint8_t* const, const size_t) const noexcept;

        private:
            Y_Disable_Copy_And_Assign(ByteIterator); //!< discarded
            const uint8_t * entry;                   //!< inner cursor
        };


        //______________________________________________________________________
        //
        //
        //
        //! Iterator on uint16_t array
        //
        //
        //______________________________________________________________________
        template <>
        class ByteIterator<uint16_t>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! inner state
            enum State
            {
                Return0, //!< need to return first byte of a word
                Return1  //!< need to return second byte of a word
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            ByteIterator(const uint16_t * const) noexcept; //!< setup from user's data
            ~ByteIterator()                      noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            //! \return next byte, read only what is necessary
            uint8_t operator()(void) noexcept;

            //! \return true if cursor is within given memory area
            bool    within(const uint16_t* const, const size_t) const noexcept;

        private:
            Y_Disable_Copy_And_Assign(ByteIterator); //!< discarded
            const uint16_t * entry; //!< current cursor
            uint16_t         word;  //!< current word
            State            state; //!< current state

        };

        //______________________________________________________________________
        //
        //
        //
        //! Iterator on uint32_t array
        //
        //
        //______________________________________________________________________
        template <>
        class ByteIterator<uint32_t>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! Inner state
            enum State
            {
                Return0, //!< need to return first  byte
                Return1, //!< need to return second byte
                Return2, //!< need to return third  byte
                Return3  //!< need to return fourth byte
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            ByteIterator(const uint32_t * const) noexcept; //!< setup from user's data
            ~ByteIterator()                      noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return next byte, read only what is necessary
            uint8_t operator()(void) noexcept;

            //! \return true if cursor is within given memory area
            bool    within(const uint32_t* const, const size_t) const noexcept;


        private:
            Y_Disable_Copy_And_Assign(ByteIterator); //!< discarded
            const uint32_t * entry; //!< current cursor
            uint32_t         dword; //!< current dword
            State            state; //!< current state


        };




    }
}


#endif // !Y_Apex_Iterator_Included
