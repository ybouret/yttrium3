#include "y/random/bits.hpp"
#include "y/type/destroy.hpp"
#include "y/core/min.hpp"

#include <iostream>
#include <cmath>
#include <cfloat>

namespace Yttrium
{
    namespace Random
    {

        namespace
        {
            template <typename T>
            class Metrics
            {
            public:
                typedef T (Metrics::*Get)(const uint32_t) const;

                static const T        EPSILON; //!< numeric epsilon
                static const unsigned MAX_SHL; //!< theoretical denom : 2^MAX_SHL
                static const unsigned TOP_SHL; //!< min(32,MAX_SHL)
                static const uint32_t TOP_U32; //!< 2^TOP_SHL - 1
                static const T        TOP_DEN; //!< 2^TOP_SHL
                static const T        HALF;    //!< 0.5

                inline Metrics(const uint32_t umax) noexcept :
                m32(umax),
                d32( chooseD32() ),
                get( chooseGet() )
                {

                }

                inline ~Metrics() noexcept
                {

                }

                inline T eval(const uint32_t u32) const noexcept
                {
                    return (*this.*get)(u32);
                }

                const uint32_t m32;
                const T        d32;
                Get const      get;

            private:
                Y_Disable_Copy_And_Assign(Metrics);

                inline T chooseD32() const noexcept
                {
                    if(m32<TOP_U32)
                    {
                        //std::cerr << "Cut D32 @" << ( (T)m32+1 ) << std::endl;
                        return (T) m32+1;
                    }
                    else
                    {
                        //std::cerr << "Top D2 @" << TOP_DEN << std::endl;
                        return TOP_DEN;
                    }
                }

                inline Get chooseGet() const noexcept
                {
                    if(m32<=TOP_U32)
                        return & Metrics:: getFull;
                    else
                        return & Metrics:: getComp;
                }

                T getFull(const uint32_t u32) const noexcept
                {
                    return ( HALF + (T)u32 ) / d32;

                }

                T getComp(const uint32_t u32) const noexcept
                {
                    uint64_t u64 = u32;
                    u64 *= TOP_U32;
                    u64 /= m32;
                    return getFull( (uint32_t) u64 );
                }

            };

            template <> const float       Metrics<float>       :: EPSILON = FLT_EPSILON;
            template <> const double      Metrics<double>      :: EPSILON = DBL_EPSILON;
            template <> const long double Metrics<long double> :: EPSILON = LDBL_EPSILON;

            template <> const float       Metrics<float>       :: HALF = 0.5f;
            template <> const double      Metrics<double>      :: HALF = 0.5;
            template <> const long double Metrics<long double> :: HALF = 0.5L;

            template <> const unsigned Metrics<float>::       MAX_SHL = (unsigned) floorf( - logf(EPSILON) / logf(2.0f) - 1.0f );
            template <> const unsigned Metrics<double>::      MAX_SHL = (unsigned) floor(  - log(EPSILON)  / log(2.0)   - 1.0  );
            template <> const unsigned Metrics<long double>:: MAX_SHL = (unsigned) floorl( - logl(EPSILON) / logl(2.0L) - 1.0L );

            template <> const unsigned Metrics<float>::       TOP_SHL = Min<unsigned>(MAX_SHL,32);
            template <> const unsigned Metrics<double>::      TOP_SHL = Min<unsigned>(MAX_SHL,32);
            template <> const unsigned Metrics<long double>:: TOP_SHL = Min<unsigned>(MAX_SHL,32);

            namespace
            {

                uint32_t GetTopU32(const unsigned top_shl) noexcept
                {
                    assert(top_shl<=32);

                    static const uint32_t one = 1;
                    switch(top_shl)
                    {
                        case 32: return 0xffffffff;
                        default: break;
                    }
                    return (one<<top_shl) - one;
                }


                template <typename T> static inline
                T GetTopDen(const unsigned top_shl) noexcept
                {
                    assert(top_shl<=32);

                    static const uint32_t one = 1;
                    switch(top_shl)
                    {
                        case 32: return (T) 4294967296;
                        default: break;
                    }
                    return (T)(one<<top_shl);
                };
            }

            template <> const uint32_t    Metrics<float>::       TOP_U32 = GetTopU32(TOP_SHL);
            template <> const uint32_t    Metrics<double>::      TOP_U32 = GetTopU32(TOP_SHL);
            template <> const uint32_t    Metrics<long double>:: TOP_U32 = GetTopU32(TOP_SHL);

            template <> const float       Metrics<float>::       TOP_DEN = GetTopDen<float>(TOP_SHL);
            template <> const double      Metrics<double>::      TOP_DEN = GetTopDen<double>(TOP_SHL);
            template <> const long double Metrics<long double>:: TOP_DEN = GetTopDen<long double>(TOP_SHL);
        }



        class Bits:: Code : public Object
        {
        public:
            inline explicit Code(const uint32_t umax) noexcept :
            f(umax),
            d(umax),
            D(umax)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

            const Metrics<float>       f;
            const Metrics<double>      d;
            const Metrics<long double> D;

        private:
            Y_Disable_Copy_And_Assign(Code);

        };

        Bits:: ~Bits() noexcept
        {
            Destroy(code);
        }

        
        Bits:: Bits(const uint32_t umax)   :
        code( new Code(umax) )
        {

        }

        template <> float       Bits:: get<float>()       noexcept { assert(code); return code->f.eval( next32() ); }
        template <> double      Bits:: get<double>()      noexcept { assert(code); return code->d.eval( next32() ); }
        template <> long double Bits:: get<long double>() noexcept { assert(code); return code->D.eval( next32() ); }

        template <> XReal<float>       Bits:: get< XReal<float> >()       noexcept { assert(code); return code->f.eval( next32() ); }
        template <> XReal<double>      Bits:: get< XReal<double> >()      noexcept { assert(code); return code->d.eval( next32() ); }
        template <> XReal<long double> Bits:: get< XReal<long double> >() noexcept { assert(code); return code->D.eval( next32() ); }


        double Bits:: operator()() noexcept { assert(code); return code->d.eval( next32() ); }

        template <>
        uint8_t Bits:: get<uint8_t>() noexcept
        {
            assert( code );
            const double r = code->d.eval( next32() );
            return (uint8_t) floor( 255.0 * r + 0.5);
        }

        template <>
        uint16_t Bits:: get<uint16_t>() noexcept
        {
            assert( code );
            const double r = code->d.eval( next32() );
            return (uint16_t) floor(65535.0 * r + 0.5);
        }

        template <>
        uint32_t Bits:: get<uint32_t>() noexcept
        {
            assert( code );
            const double r = code->d.eval( next32() );
            return (uint32_t) floor(4294967296.0 * r + 0.5);
        }

        template <>
        uint64_t Bits:: get<uint64_t>() noexcept
        {
            assert( code );
            uint64_t u64 = get<uint32_t>();
            /**/     u64 <<= 32;
            /**/     u64 |= get<uint32_t>();
            return u64;
        }





#if 0
        double Bits:: operator()() noexcept
        {
            static const double half = 0.5;
            return ( half + (double)next32()   )/denom;
        }
#endif

#if 0
        double Bits:: symm32() noexcept
        {
            const double u = (*this)();
            return 1.0 - (u+u);
        }
#endif

       // template <> double       Bits:: to<double>()       noexcept { return (*this)(); }
       // template <> float        Bits:: to<float>()        noexcept { return (float)((*this)()); }
       // template <> long double  Bits:: to<long double>()  noexcept { return (long double)((*this)()); }


      //template <> XReal<double> Bits:: to< XReal<double> >() noexcept { return to<double>(); }

      //template <> uint32_t Bits:: to<uint32_t>() noexcept { return next32(); }
      //template <> uint16_t Bits:: to<uint16_t>() noexcept { return (uint16_t)next32(); }
      //template <> uint8_t  Bits:: to<uint8_t>() noexcept { return (uint8_t)next32(); }


      //template <>
      //uint64_t Bits:: to<uint64_t>() noexcept
      //{
      //    const uint64_t lo = next32();
      //    const uint64_t hi = next32();
      //    return lo | (hi<<32);
      //}

      //template <> double       Bits:: symm<double>()       noexcept { return               symm32(); }
      //template <> float        Bits:: symm<float>()        noexcept { return (float)       symm32(); }
      //template <> long double  Bits:: symm<long double>()  noexcept { return (long double) symm32(); }

    }

}


