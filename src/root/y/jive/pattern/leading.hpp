
//! \file

#ifndef Y_Jive_Leading_Included
#define Y_Jive_Leading_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Leading first byte
        //
        //
        //______________________________________________________________________
        class Leading
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint8_t Bit[8]; //!< Bits
            static const uint8_t Msk[8]; //!< ~Bit

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Leading()                            noexcept; //!< setup empty
            ~Leading()                           noexcept; //!< cleanup
            Leading(const Leading &)             noexcept; //!< duplicate
            Leading & operator=(const Leading &) noexcept; //!< assign \return *this
            Y_OSTREAM_PROTO(Leading);                      //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Leading & operator << (const uint8_t)   noexcept; //!< merge byte \return *this
            Leading & operator << (const Leading &) noexcept; //!< merge another \return *this

            bool      get(const uint8_t)          const noexcept; //!< get byte status \return true iff byte is use
            Leading & set(const uint8_t)                noexcept; //!< set byte status \return *this
            Leading & clr(const uint8_t)                noexcept; //!< clr byte status \return *this
            Leading & ldz()                             noexcept; //!< reset \return *this
            Leading & all()                             noexcept; //!< set all used \return *this
            Leading & set(const uint8_t, const uint8_t) noexcept; //!< set a range \return *this

            size_t size() const noexcept; //!< \return number of used bytes


        private:
            uint8_t data[32]; //!< 256 bits
        };
    }

}

#endif // !Y_Jive_Leading_Included
