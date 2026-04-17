

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {

#define Y_APQ_DECL(RET,CALL)                         \
static RET CALL(const Rational &, const Rational &); \
static RET CALL(const Rational &, const Integer  &); \
static RET CALL(const Integer  &, const Rational &); \
static RET CALL(const Rational &, const Natural  &); \
static RET CALL(const Natural  &, const Rational &); \
static RET CALL(const Rational &, const integer_t ); \
static RET CALL(const integer_t,  const Rational &); \

#define Y_APQ_CMP(OP,EXPR) \
inline friend bool operator OP (const Rational & lhs, const Rational & rhs) { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const Rational & lhs, const Integer  & rhs) { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const Integer  & lhs, const Rational & rhs) { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const Rational & lhs, const Natural  & rhs) { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const Natural  & lhs, const Rational & rhs) { return Cmp(lhs,rhs) EXPR; } \


        //______________________________________________________________________
        //
        //
        //
        //! Rational number
        //
        //
        //______________________________________________________________________
        class Rational : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "apq"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Rational();                  //!< zero
            Rational(const Rational &);  //!< duplicate
            Rational(const Natural  &);  //!< duplicate
            Rational(const Integer  &);  //!< duplicate
            Rational(const integer_t);   //!< duplicate

            Rational(const Integer &, const Natural &); //!< setup as fraction
            Rational(const Integer &, const natural_t); //!< setup as fraction
            Rational(const integer_t, const Natural &); //!< setup as fraction
            Rational(const integer_t, const natural_t); //!< setup as fraction
            Rational(const Fraction);                   //!< setup as fraction
            Rational(Random::CoinFlip &, const size_t, const size_t); //!< setup random


            virtual ~Rational() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Rational);    //!< display

            //__________________________________________________________________
            //
            //
            // Inteface
            //
            //__________________________________________________________________
            virtual void         ldz()            noexcept;
            virtual bool         is0()      const noexcept;
            virtual const char * callSign() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String     toDec()              const; //!< \return decimal representation
            Rational & xch( Rational & ) noexcept; //!< \return no-throw exchange


            //__________________________________________________________________
            //
            //
            // Comparisons
            //
            //__________________________________________________________________
            friend bool operator==(const Rational &, const Rational &) noexcept;
            friend bool operator==(const Rational &, const Integer  &) noexcept;
            friend bool operator==(const Integer  &, const Rational &) noexcept;
            friend bool operator==(const Rational &, const integer_t ) noexcept;
            friend bool operator==(const integer_t,  const Rational &) noexcept;
            friend bool operator==(const Rational &, const Natural  &) noexcept;
            friend bool operator==(const Natural  &, const Rational &) noexcept;
            
            friend bool operator!=(const Rational &, const Rational &) noexcept;
            friend bool operator!=(const Rational &, const Integer  &) noexcept;
            friend bool operator!=(const Integer  &, const Rational &) noexcept;
            friend bool operator!=(const Rational &, const integer_t ) noexcept;
            friend bool operator!=(const integer_t,  const Rational &) noexcept;
            friend bool operator!=(const Rational &, const Natural  &) noexcept;
            friend bool operator!=(const Natural  &, const Rational &) noexcept;


            Y_APQ_DECL(SignType,Cmp);
            Y_APQ_CMP(<, == Negative)
            Y_APQ_CMP(>, == Positive)
            Y_APQ_CMP(<=,!= Positive)
            Y_APQ_CMP(>=,!= Negative)
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Integer numer; //!< numerator
            const Natural denom; //!< denominator >= 1

        private:
            void reduce(); //!< to irreducible form
        };
    }

    typedef Apex::Rational apq; //!< alias

}

#endif // !Y_Apex_Rational_Included

