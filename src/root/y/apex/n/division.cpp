#include "y/apex/n/code.hpp"
#include "y/apex/k/div.hpp"


namespace Yttrium
{
    namespace Apex
    {
        namespace
        {
            enum DivOuput
            {
                DivOutputNone,
                DivOutputQuot,
                DivOutputRem,
                DivOutputBoth
            };

            static inline DivOuput DivOutputFor(const void * q, const void *r) noexcept
            {
                if(q)
                {
                    if(r)
                    {
                        assert(q&&r);
                        return DivOutputBoth;
                    }
                    else
                    {
                        assert(q&&!r);
                        return DivOutputQuot;
                    }
                }
                else
                {
                    if( r )
                    {
                        assert(!q&&r);
                        return DivOutputRem;
                    }
                    else
                    {
                        assert(!q&&!r);
                        return DivOutputNone;
                    }
                }
            }
        }


        bool Natural:: DivCall(Natural * const quot,
                               Natural * const rem,
                               const void * const numerAddr, const size_t nsize,
                               const void * const denomAddr, const size_t dsize)
        {
            typedef _Keg::Word       WordType;
            typedef _Keg::Core       CoreType;
            typedef Keg<WordType>    KegType;
            typedef AutoPtr<KegType> KegPtr;
            const WordType * const numer = static_cast<const WordType *>(numerAddr);
            const WordType * const denom = static_cast<const WordType *>(denomAddr);
            switch( DivOutputFor(quot,rem) )
            {
                case DivOutputNone:
                    assert(!quot); assert(!rem);
                    return KegDiv::Compute<WordType,CoreType>(0,0,numer,nsize,denom,dsize);

                case DivOutputQuot: {
                    assert(quot); assert(!rem);
                    KegPtr Q = 0;
                    const bool divisible = KegDiv::Compute<WordType,CoreType>(&Q,0,numer,nsize,denom,dsize);
                    assert(Q.isValid());
                    delete static_cast<KegType *>(quot->code);
                    Coerce(quot->code) = Q.yield();
                    return divisible;
                }

                case DivOutputRem: {
                    assert(!quot); assert(rem);
                    KegPtr R = 0;
                    const bool divisible = KegDiv::Compute<WordType,CoreType>(0,&R,numer,nsize,denom,dsize);
                    assert(R.isValid());
                    delete static_cast<KegType *>(rem->code);
                    Coerce(rem->code) = R.yield();
                    return divisible;
                }

                case DivOutputBoth: {
                    assert(quot); assert(rem);
                    KegPtr Q = 0;
                    KegPtr R = 0;
                    const bool divisible = KegDiv::Compute<WordType,CoreType>(&Q,&R,numer,nsize,denom,dsize);
                    assert(Q.isValid());
                    assert(R.isValid());
                    delete static_cast<KegType *>(quot->code); Coerce(quot->code) = Q.yield();
                    delete static_cast<KegType *>(rem->code);  Coerce(rem->code)  = R.yield();
                    return divisible;
                }
            }

#if (defined(__GNUC__) && !defined(__clang__)) || defined(_MSC_VER)
            // never get here
            return false;
#endif
            
        }

        bool Natural:: Division(Natural * const quot,
                                Natural * const rem,
                                const Natural & numer,
                                const Natural & denom)
        {
            const KegType & N = *static_cast<const KegType *>(numer.code);
            const KegType & D = *static_cast<const KegType *>(denom.code);
            return DivCall(quot,rem, N.word, N.words, D.word, D.words);
        }

        bool Natural:: Division(Natural * const quot,
                                Natural * const rem,
                                const Natural & numer,
                                const natural_t denom)
        {
            const KegType &   N = *static_cast<const KegType *>(numer.code);
            const PreComputed D(denom);
            return DivCall(quot,rem, N.word, N.words, D.word, D.words);
        }


        bool Natural:: Division(Natural * const quot,
                                Natural * const rem,
                                const natural_t numer,
                                const Natural & denom)
        {
            const PreComputed N(numer);
            const KegType &   D = *static_cast<const KegType *>(denom.code);
            return DivCall(quot,rem, N.word, N.words, D.word, D.words);
        }
    }
}
