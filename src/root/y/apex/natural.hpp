
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/string.hpp"
#include "y/type-to-type.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/random/coin-flip.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {


        //! helper to implement comparisons
#define Y_Apex_Natural_Cmp(OP,EXPR) \
inline friend bool operator OP (const Natural & lhs, const Natural & rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const Natural & lhs, const natural_t rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const natural_t lhs, const Natural & rhs) noexcept { return Cmp(lhs,rhs) EXPR; }

        //! helper to declare all possible methods
#define Y_Apex_Natural_Decl(METH) \
static Natural METH(const Natural & lhs, const Natural & rhs);\
static Natural METH(const Natural & lhs, const natural_t rhs);\
static Natural METH(const natural_t lhs, const Natural & rhs)


        //! helper to implement binary operators
#define Y_Apex_Natural_Binary(OP,CALL) \
inline friend Natural operator OP (const Natural & lhs, const Natural & rhs) { return CALL(lhs,rhs); }\
inline friend Natural operator OP (const Natural & lhs, const natural_t rhs) { return CALL(lhs,rhs); }\
inline friend Natural operator OP (const natural_t lhs, const Natural & rhs) { return CALL(lhs,rhs); }

        //! helper to implement unary operators
#define Y_Apex_Natural_Unary(OP,CALL) \
inline Natural & operator OP##=(const Natural & rhs) { Natural tmp = CALL(*this,rhs); return xch(tmp); } \
inline Natural & operator OP##=(const natural_t rhs) { Natural tmp = CALL(*this,rhs); return xch(tmp); }

        //! helper to implement operators
#define Y_Apex_Natural(OP,CALL) \
Y_Apex_Natural_Decl(CALL);      \
Y_Apex_Natural_Binary(OP,CALL)  \
Y_Apex_Natural_Unary(OP,CALL)

        class Integer;

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
            static const char * const   CallSign;  //!< "apn"
            typedef TypeToType<Natural> Directly_; //!< alias
            static const Directly_      Directly;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Natural();                                       //!< setup 0
            Natural(const natural_t);                        //!< setup to given value
            Natural(const Natural &);                        //!< duplicate
            Natural & operator=(const Natural &);            //!< assign \return *this
            Natural & operator=(const natural_t);            //!< assign \return *this
            virtual ~Natural() noexcept;                     //!< cleanup
            Y_OSTREAM_PROTO(Natural);                        //!< display
            Natural(const TwoToThePowerOf_ &, const size_t); //!< set as power of two
            Natural(Random::CoinFlip &, const size_t);       //!< set with exact bit count, random

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;
            virtual void ldz()                    noexcept;
            virtual bool is0()              const noexcept;
            virtual bool is1()              const noexcept;
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Natural & xch(Natural &) noexcept;       //!< no-throw exchange \return *this
            String    toHex()        const;          //!< \return hexadecimal content
            String    toBin()        const;          //!< \return binary content
            String    toDec()        const;          //!< \return decimal constent
            natural_t lsw()          const noexcept; //!< \return least significant word

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            //__________________________________________________________________
            //
            //
            // Comparisons
            //
            //__________________________________________________________________
            static SignType Cmp(const Natural &lhs, const Natural & rhs) noexcept;
            static SignType Cmp(const Natural &lhs, natural_t       rhs) noexcept;
            static SignType Cmp(natural_t      lhs, const Natural & rhs) noexcept;

            Y_Apex_Natural_Cmp(==, == __Zero__)
            Y_Apex_Natural_Cmp(!=, != __Zero__)
            Y_Apex_Natural_Cmp(<,  == Negative)
            Y_Apex_Natural_Cmp(>,  == Positive)
            Y_Apex_Natural_Cmp(<=, != Positive)
            Y_Apex_Natural_Cmp(>=, != Negative)

            //__________________________________________________________________
            //
            //
            // Additions
            //
            //__________________________________________________________________
            Natural   operator+() const;
            Y_Apex_Natural(+,Add)
            Natural        successor() const;
            Natural & operator++();      //!< prefix
            Natural   operator++(int);   //!< postfix

            //__________________________________________________________________
            //
            //
            // Subtraction
            //
            //__________________________________________________________________
            Integer   operator-()   const;
            Natural   predecessor() const;
            Y_Apex_Natural(-,Sub)
            Natural & operator--();    //!< prefix
            Natural   operator--(int); //!< postfix

            //__________________________________________________________________
            //
            //
            // Multiplication
            //
            //__________________________________________________________________
            Y_Apex_Natural(*,Mul)


            //__________________________________________________________________
            //
            //
            // Division
            //
            //__________________________________________________________________
            static bool Division(Natural * const quot,
                                 Natural * const rem,
                                 const Natural & numer,
                                 const Natural & denom);

            static bool Division(Natural * const quot,
                                 Natural * const rem,
                                 const Natural & numer,
                                 const natural_t denom);

            static bool Division(Natural * const quot,
                                 Natural * const rem,
                                 const natural_t numer,
                                 const Natural & denom);

            Y_Apex_Natural(/,Div)

            //__________________________________________________________________
            //
            //
            // Modulo
            //
            //__________________________________________________________________
            Y_Apex_Natural(%,Modulo)
            
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


            //__________________________________________________________________
            //
            //
            // Bits
            //
            //__________________________________________________________________
            Natural & shr()        noexcept;        //!< \return fast division by two
            Natural & shl();                        //!< \return multiplication by two
            size_t    bits() const noexcept;        //!< \return number of bits
            Natural & shr(const size_t n) noexcept; //!< \param n bits to shift \return *this >>= n
            Natural & shl(const size_t n);          //!< \param n bits to shift \return *this <<= n

            //__________________________________________________________________
            //
            //
            // Arithmetic
            //
            //__________________________________________________________________
            Natural        abs()  const; //!< \return |*this|
            Natural        sqrt() const; //!< \return sqrt(*this)
            static Natural GCD(const Natural &, const Natural &); //!< \return GCD of arguments
            static void    Reduce(Natural &, Natural &); //!< representation reduction
            
            //__________________________________________________________________
            //
            //
            // Counting
            //
            //__________________________________________________________________
            static Natural factorial(const natural_t n); //!< \param n integral value \return n!

            //__________________________________________________________________
            //
            //
            // Cast
            //
            //__________________________________________________________________

            //! try to cast
            /**
             \param result target
             \return true iff possible cast
             */
            template <typename T> inline
            bool tryCast(T &result) const noexcept
            {
                static const natural_t MaxValue = (natural_t) IntegerFor<T>::Maximum;
                if( *this > MaxValue ) return false;
                const natural_t self = lsw(); assert(self<MaxValue);
                result = (T)self;
                return true;
            }

            //! cast with checking
            /**
             \param varName optional var name
             \param varPart optional var part
             \return casted value
             */
            template <typename T> inline
            T cast(const char * const varName, const char * const varPart)
            {
                T res = 0;
                if(!tryCast(res)) {
                    Specific::Exception excp(CallSign,"cast overflow");
                    throw excp.signedFor(varName,varPart);
                }
                return res;
            }

        private:
            void * const code; //!< inner code

            //! setup code directly
            Natural( const Directly_ &, void * const) noexcept;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static bool DivCall(Natural * const, Natural * const,
                                const void * const, const size_t,
                                const void * const, const size_t);



#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };
    }

    typedef Apex::Natural apn; //!< alias

}

#endif // !Y_Apex_Natural_Included

