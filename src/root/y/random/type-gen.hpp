
//! \file

#ifndef Y_Random_TypeGen_Included
#define Y_Random_TypeGen_Included 1

#include "y/random/coin-flip.hpp"
#include "y/type/ints.hpp"
#include "y/apex/rational.hpp"
#include "y/core/twice.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/v4d.hpp"

namespace Yttrium
{
    namespace Random
    {

        struct GenInfo
        {
            static size_t       MaxStringLength; //!< default to 8
            static const size_t MaxApexBits = 11;
        };

        template <typename T>
        struct Gen
        {
            static inline T Get(Random::CoinFlip &coin)
            {
                typedef typename UnsignedFor<sizeof(T)>::Alias::Type U;
                static const unsigned Bits = sizeof(U) * 8;
                static const U        One  = 1;
                U u = 0;
                for(unsigned i=Bits;i>0;--i) {
                    u <<= 1;
                    if(coin.heads()) u |= One;
                }
                union {
                    U word;
                    T type;
                } alias = { u };
                return alias.type;
            }
        };

        template <>
        struct Gen<char>
        {
            static inline char Get(Random::CoinFlip &coin) {
                return (char)(32+coin.toss<uint8_t>(126-32));
            }
        };

        template <>
        struct Gen<String>
        {
            static inline String Get(Random::CoinFlip &coin)
            {
                String res;
                for(size_t i=1+coin.toss<size_t>(GenInfo::MaxStringLength-1);i>0;--i)
                    res += Gen<char>::Get(coin);
                return res;
            }
        };

        template <>
        struct Gen<apn>
        {
            static inline apn Get(Random::CoinFlip &coin)
            {
                return apn(coin,coin.toss<size_t>(GenInfo::MaxApexBits));
            }
        };

        template <>
        struct Gen<apz>
        {
            static inline apz Get(Random::CoinFlip &coin)
            {
                return apz(coin,coin.toss<size_t>(GenInfo::MaxApexBits));
            }
        };

        template <>
        struct Gen<apq>
        {
            static inline apq Get(Random::CoinFlip &coin)
            {
                return apq(coin,coin.toss<size_t>(GenInfo::MaxApexBits),coin.toss<size_t>(GenInfo::MaxApexBits));
            }
        };

        template <> struct Gen<float> {
            static inline float Get(Random::CoinFlip &coin) {
                return 1.0f - Twice(coin.uniform<float>());
            }
        };

        template <> struct Gen<double> {
            static inline double Get(Random::CoinFlip &coin) {
                return 1.0 - Twice(coin.uniform<double>());
            }
        };

        template <> struct Gen<long double> {
            static inline long double Get(Random::CoinFlip &coin) {
                return 1.0L - Twice(coin.uniform<long double>());
            }
        };

        template <typename T> struct Gen< XReal<T> >
        {
            static inline XReal<T> Get(Random::CoinFlip &coin)
            {
                return Gen<T>::Get(coin);
            }
        };

        template <typename T> struct Gen< Complex<T> >
        {
            static inline Complex<T> Get(Random::CoinFlip &coin)
            {
                return Complex<T>(Gen<T>::Get(coin),Gen<T>::Get(coin));
            }
        };

        template <typename T> struct Gen< V2D<T> >
        {
            static inline V2D<T> Get(Random::CoinFlip &coin)
            {
                return V2D<T>(Gen<T>::Get(coin),Gen<T>::Get(coin));
            }
        };

        template <typename T> struct Gen< V3D<T> >
        {
            static inline V3D<T> Get(Random::CoinFlip &coin)
            {
                return V3D<T>(Gen<T>::Get(coin),Gen<T>::Get(coin),Gen<T>::Get(coin));
            }
        };

        struct Generate
        {
            template <typename ARRAY> static inline
            void Array(Random::CoinFlip &coin, ARRAY &arr)
            {
                for(size_t i=arr.size();i>0;--i)
                {
                    arr[i] = Gen< typename ARRAY::Type >::Get(coin);
                }
            }

            template <typename MATRIX> static inline
            void Matrix(Random::CoinFlip &coin, MATRIX &a)
            {
                for(size_t i=a.rows;i>0;--i)
                {
                    for(size_t j=a.cols;j>0;--j)
                    {
                         a[i][j] = Gen< typename MATRIX::Type >::Get(coin);
                    }
                }
            }
        };


    }

}

#endif // !Y_Random_TypeGen_Included
