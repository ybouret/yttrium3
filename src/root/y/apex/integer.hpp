
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //! helper to implement comparisons
#define Y_Integer_Cmp(OP,EXPR) \
inline friend bool operator OP ( const Integer & lhs, const Integer & rhs ) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP ( const Integer & lhs, const Natural & rhs ) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP ( const Natural & lhs, const Integer & rhs ) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP ( const Integer & lhs, const integer_t rhs ) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP ( const integer_t lhs, const Integer & rhs ) noexcept { return Cmp(lhs,rhs) EXPR; }

        //! helper to implement binary operators
#define Y_Integer_Binary(OP,CALL) \
inline friend Integer operator OP ( const Integer & lhs, const Integer & rhs ) { return CALL(lhs,rhs); } \
inline friend Integer operator OP ( const Integer & lhs, const Natural & rhs ) { return CALL(lhs,rhs); } \
inline friend Integer operator OP ( const Natural & lhs, const Integer & rhs ) { return CALL(lhs,rhs); } \
inline friend Integer operator OP ( const Integer & lhs, const integer_t rhs ) { return CALL(lhs,rhs); } \
inline friend Integer operator OP ( const integer_t lhs, const Integer & rhs ) { return CALL(lhs,rhs); } \

        //! helper to implement unary operators
#define Y_Integer_Unary(OP,CALL) \
inline Integer & operator OP##= (const Integer & rhs ) { Integer tmp = CALL(*this,rhs); return xch(tmp); } \
inline Integer & operator OP##= (const Natural & rhs ) { Integer tmp = CALL(*this,rhs); return xch(tmp); } \
inline Integer & operator OP##= (const integer_t rhs ) { Integer tmp = CALL(*this,rhs); return xch(tmp); }

        //! helper to implement all operators
#define Y_Integer_Impl(OP,CALL) Y_Integer_Binary(OP,CALL) Y_Integer_Unary(OP,CALL)

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


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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

            Y_Integer_Cmp(==, == __Zero__ )
            Y_Integer_Cmp(!=, != __Zero__ )
            Y_Integer_Cmp(<,  == Negative )
            Y_Integer_Cmp(>,  == Positive )
            Y_Integer_Cmp(<=, != Positive )
            Y_Integer_Cmp(>=, != Negative )


            //__________________________________________________________________
            //
            //
            // Additions
            //
            //__________________________________________________________________
            static Integer  Add(const Integer & lhs, const Integer & rhs);
            static Integer  Add(const Integer & lhs, const Natural & rhs);
            static Integer  Add(const Natural & lhs, const Integer & rhs);
            static Integer  Add(const Integer & lhs, const integer_t rhs);
            static Integer  Add(const integer_t lhs, const Integer & rhs);

            Y_Integer_Impl(+,Add)

            Integer   operator+() const;  //!< unary
            Integer & operator++();      //!< prefix
            Integer   operator++(int);   //!< postfix
            Integer   successor() const;
            
            //__________________________________________________________________
            //
            //
            // Subtractions
            //
            //__________________________________________________________________
            static Integer  Sub(const Integer & lhs, const Integer & rhs);
            static Integer  Sub(const Integer & lhs, const Natural & rhs);
            static Integer  Sub(const Natural & lhs, const Integer & rhs);
            static Integer  Sub(const Integer & lhs, const integer_t rhs);
            static Integer  Sub(const integer_t lhs, const Integer & rhs);

            Y_Integer_Impl(-,Sub)

            Integer operator-() const;
            Integer & operator--();        //!< prefix
            Integer   operator--(int);     //!< postfix
            Integer   predecessor() const;

            //__________________________________________________________________
            //
            //
            // Multiplications
            //
            //__________________________________________________________________
            static Integer  Mul(const Integer & lhs, const Integer & rhs);
            static Integer  Mul(const Integer & lhs, const Natural & rhs);
            static Integer  Mul(const Natural & lhs, const Integer & rhs);
            static Integer  Mul(const Integer & lhs, const integer_t rhs);
            static Integer  Mul(const integer_t lhs, const Integer & rhs);

            Y_Integer_Impl(*,Mul)

            //__________________________________________________________________
            //
            //
            // Divisions
            //
            //__________________________________________________________________
            static Integer  Div(const Integer & lhs, const Integer & rhs);
            static Integer  Div(const Integer & lhs, const Natural & rhs);
            static Integer  Div(const Natural & lhs, const Integer & rhs);
            static Integer  Div(const Integer & lhs, const integer_t rhs);
            static Integer  Div(const integer_t lhs, const Integer & rhs);

            Y_Integer_Impl(/,Div)

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const SignType s; //!< sign
            const Natural  n; //!< absolute value

        private:
            //! specific constructor
            Integer(const SignType, const Natural &);
        };
    }

    typedef Apex::Integer apz; //!< alias

}

#endif // !Y_Apex_Integer_Included

