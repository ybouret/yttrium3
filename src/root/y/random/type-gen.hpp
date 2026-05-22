
//! \file

#ifndef Y_Random_TypeGen_Included
#define Y_Random_TypeGen_Included 1

#include "y/random/coin-flip.hpp"
#include "y/type/ints.hpp"
#include "y/apex/rational.hpp"

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


    }

}

#endif // !Y_Random_TypeGen_Included
