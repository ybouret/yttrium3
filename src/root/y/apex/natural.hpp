
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
#include "y/mkl/xreal.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        // Helpers for ratio
        //
        //
        //______________________________________________________________________

        template <typename T> struct RealDigits;

        //! digits for float
        template <> struct RealDigits<float>       { static const unsigned Count = FLT_DIG; /*!< FLT_DIG */  };

        //! digits for double
        template <> struct RealDigits<double>      { static const unsigned Count = DBL_DIG;  /*!< DBL_DIG */};

        //! digits for long double
        template <> struct RealDigits<long double> { static const unsigned Count = LDBL_DIG; /*!< LDBL_DIG */};

        //! digits for associated XReal
        template <typename T> struct RealDigits< XReal<T> > { static const unsigned Count = RealDigits<T>::Count; /*!< alias */  };

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
            Natural & shr()        noexcept;                  //!< \return fast division by two
            Natural & shl();                                  //!< \return multiplication by two
            size_t    bits() const noexcept;                  //!< \return number of bits
            size_t    bytes() const noexcept;                 //!< \return number of bytes

            Natural & shr(const size_t n) noexcept; //!< \param n bits to shift \return *this >>= n
            Natural & shl(const size_t n);          //!< \param n bits to shift \return *this <<= n

            Natural & operator<<=(const size_t); //!< left shift \return *this
            Natural & operator>>=(const size_t); //!< right shift \return *this

            friend Natural  operator<<(const Natural &, const size_t); //!< \return left  shift
            friend Natural  operator>>(const Natural &, const size_t); //!< \return right shift


            //! find byte at given position
            /**
             \param ibyte in [0:bytes()-1] or 0
             \return ibytes-th byte, always ok for ibytes==0
             */
            uint8_t   operator[](const size_t ibyte) const noexcept;


            //__________________________________________________________________
            //
            //
            // Arithmetic
            //
            //__________________________________________________________________
            Natural        abs()  const; //!< \return |*this|
            Natural        sqrt() const; //!< \return sqrt(*this)
            static Natural GCD(const Natural &, const Natural &); //!< \return GCD of arguments
            static Natural LCM(const Natural &, const Natural &); //!< \return LCM of arguments
            static void    Reduce(Natural &, Natural &); //!< representation reduction
            Natural        mod2()   const;           //!< \return |*this|^2
            bool           isOdd()  const noexcept; //!< \return true iff odd
            bool           isEven() const noexcept; //!< \return true iff even


            //__________________________________________________________________
            //
            //
            // Counting
            //
            //__________________________________________________________________
            static Natural Factorial(const natural_t n);               //!< \param n integral value \return n!
            static Natural Comb(const natural_t n, const natural_t k); //!< \param n n>=0 \param k 0<=k<=n \return (n,k)

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
            T cast(const char * const varName, const char * const varPart) const
            {
                T res = 0;
                if(!tryCast(res)) {
                    Specific::Exception excp(CallSign,"cast overflow");
                    throw excp.signedFor(varName,varPart);
                }
                return res;
            }

            //! \param num numerator \param den denominator \return ratio with given precision
            template <typename T> static inline
            T Ratio(const Natural &num, const Natural &den)
            {
                static const unsigned  Digits = RealDigits<T>::Count;
                static const T         Factor = 256;
                static const T         Tenth  = T(0.1);
                static const natural_t ten    = 10;
                Natural N = num;
                Natural q,r;

                T res = 0;

                // integer part
                Division(&q,&r,N,den);
                {
                    size_t                n = q.bytes();
                    while(n-- > 0 )
                    {
                        res *= Factor;
                        res += q[n];
                    }
                }

                // fractional part
                T pos = Tenth;
                for(unsigned i=0;i<Digits;++i, pos *= Tenth)
                {
                    if(r.bits()<=0) break;
                    N.xch(r);
                    N *= ten;
                    Division(&q,&r,N,den);
                    res += pos * static_cast<T>(q[0]);
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

