
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Natural number
        //
        //
        //______________________________________________________________________
        class Natural : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "apn"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Natural();                            //!< setup 0
            Natural(const natural_t);             //!< setup to given value
            Natural(const Natural &);             //!< duplicate
            Natural & operator=(const Natural &); //!< assign \return *this
            virtual ~Natural() noexcept;          //!< cleanup
            Y_OSTREAM_PROTO(Natural);             //!< display

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Natural & xch(Natural &) noexcept; //!< no-throw exchange \return *this
            String    toHex()        const;    //!< \return hexadecimal content


        private:
            void * const code; //!< inner code

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static SignType Cmp(const Natural &lhs, const Natural & rhs) noexcept;
            static SignType Cmp(const Natural &lhs, natural_t       rhs) noexcept;
#endif

        };
    }

    typedef Apex::Natural apn; //!< alias

}

#endif // !Y_Apex_Natural_Included

