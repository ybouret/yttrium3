
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Integer number
        //
        //
        //______________________________________________________________________
        class Integer : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "apz"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Integer();                  //!< zero
            Integer(const Integer &);   //!< duplicate
            Integer(const Natural &);   //!< duplicate
            Integer(const integer_t);   //!< duplicate


            Integer & operator=(const Integer &);          //!< assign Integer \return *this
            Integer & operator=(const Natural &);          //!< assign Natural \return *this
            Integer & operator=(const integer_t) noexcept; //!< assign integral, no throw \return *this

            Y_OSTREAM_PROTO(Integer);    //!< display
            virtual ~Integer() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;
            virtual void ldz()                    noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Integer & xch( Integer & ) noexcept; //!< no-throw exchange \return *this


            //__________________________________________________________________
            //
            //
            // Comparisons
            //
            //__________________________________________________________________
            static SignType Cmp(const Integer &, const Integer &) noexcept;
            static SignType Cmp(const Integer &, const Natural &) noexcept;
            static SignType Cmp(const Natural &, const Integer &) noexcept;
            static SignType Cmp(const Integer &, const integer_t) noexcept;
            static SignType Cmp(const integer_t, const Integer &) noexcept;

            //__________________________________________________________________
            //
            //
            // Additions
            //
            //__________________________________________________________________
            static Integer  Add(const Integer &lhs, const Integer &rhs);
            Integer operator+() const;

            //__________________________________________________________________
            //
            //
            // Subtractions
            //
            //__________________________________________________________________
            Integer operator-() const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const SignType s; //!< sign
            const Natural  n; //!< absolute value

        private:
            Integer(const SignType, const Natural &);
        };
    }

    typedef Apex::Integer apz; //!< alias

}

#endif // !Y_Apex_Integer_Included

