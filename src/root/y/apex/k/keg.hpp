//! \file

#ifndef Y_Apex_Keg_Included
#define Y_Apex_Keg_Included 1

#include "y/apex/k/metrics.hpp"
#include "y/apex/types.hpp"
#include "y/calculus/alignment.hpp"
#include "y/calculus/required-bits.hpp"
#include "y/calculus/required-bytes.hpp"
#include "y/calculus/split-word.hpp"

#include "y/format/hexadecimal.hpp"
#include "y/libc/block/zeroed.h"

#include "y/type/with-at-least.hpp"
#include "y/type/copy-of.hpp"
#include "y/mkl/two-to-the-power-of.hpp"

#include "y/string.hpp"
#include "y/apex/k/bits.hpp"

#include "y/random/coin-flip.hpp"

#include <iostream>
#include <cstring>

#define Y_Apex_Trace //!< define to enable time trace

namespace Yttrium
{
    namespace Apex
    {

        //! helper to allocate blockShift/word
#define Y_Apex_Keg_Alloc() \
maxWords(0),  \
blockShift(0),\
word( AcquireWords<WORD>(Coerce(blockShift),Coerce(maxBytes),Coerce(maxWords) ) )


        //______________________________________________________________________
        //
        //
        //
        //! Keg to hold data and perform ops
        //
        //
        //______________________________________________________________________
        template <typename WORD>
        class Keg : public KegMetrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef WORD           WordType;                                  //!< storage type
            static  const size_t   WordBytes = sizeof(WordType);              //!< alias
            static  const unsigned WordShift = IntegerLog2<WordBytes>::Value; //!< alias
            static  const size_t   WordBits  = WordBytes * 8;                 //!< alias
            static  const WordType LowerBit  = 1;                             //!< alias
            static  const WordType UpperBit  = LowerBit << (WordBits-1);      //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________


            //! setup \param userBytes minimal bytes
            inline explicit Keg(const size_t userBytes = 0) :
            bits(0),
            bytes(0),
            maxBytes( userBytes ),
            words(0),
            Y_Apex_Keg_Alloc()
            {
            }

            //! setup \param n given natural_t
            inline explicit Keg(const CopyOf_ &, const natural_t n) :
            bits(0),
            bytes(0),
            maxBytes(0),
            words(0),
            Y_Apex_Keg_Alloc()
            {
                construct(n);
            }

            //! duplicate \param keg source
            inline explicit Keg(const Keg &keg) :
            KegMetrics(),
            bits(keg.bits),
            bytes(keg.bytes),
            maxBytes(bytes),
            words(keg.words),
            Y_Apex_Keg_Alloc()
            {
                memcpy(word,keg.word,words*WordBytes);
            }

            //! setup \param w foreign data \param n foreign size
            inline explicit Keg(const WordType * const w,
                                const size_t           n) :
            bits(0),
            bytes(0),
            maxBytes( n*sizeof(WordType) ),
            words(n),
            Y_Apex_Keg_Alloc()
            {
                assert(!(0==w&&n>0));
                assert(n==words);
                memcpy(word,w,n*WordBytes);
                update();
                assert(n==words);
            }

            //! setup with capacity \param numWords minimal required words
            inline explicit Keg(const WithAtLeast_ &, const size_t numWords) :
            bits(0),
            bytes(0),
            maxBytes( CheckedBytes(numWords*WordBytes) ),
            words(0),
            Y_Apex_Keg_Alloc()
            {
                assert(maxWords>=numWords);
            }


            //! setup to 2^n \param n exponent
            inline explicit Keg(const TwoToThePowerOf_ &, const size_t n) :
            bits(n+1),
            bytes( Alignment::On<8>::Ceil(bits) / 8),
            maxBytes( bytes ),
            words( Alignment::To<WordType>::Ceil(bytes) / WordBytes ),
            Y_Apex_Keg_Alloc()
            {
                assert(words>0);
                static const WordType _1 = 1;
                const size_t msi = words-1;   // most significant index
                WordType    &msw = word[msi]; // most significant word
                const size_t idx = n - (msi*WordBits);
                assert(idx<WordBits);
                msw = (WordType)( _1 << idx );
            }



            //! cleanup
            inline virtual ~Keg() noexcept { ReleaseWords(word,blockShift); }

            //! display
            inline friend std::ostream & operator<<( std::ostream &os, const Keg &keg)
            {
                Hexadecimal::Display(os,keg.word,keg.words);
                os << "#bits=" << keg.bits << "|bytes=" << keg.bytes;
                // if(WordBytes>1) os << "|words=" << keg.words;
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            static Keg * Zero()  { return new Keg(0); }           //!< \return zero
            static Keg * One()   { return new Keg(CopyOf,1); }    //!< \return one
            static Keg * Two()   { return new Keg(CopyOf,2); }    //!< \return two
            inline bool  leqz() const noexcept { return words<=0; } //!< \return *this <=0
            inline bool  leq1() const noexcept
            { return (words<=0) || ( (1==words) && (word[0] <= 1) ); } //!< \return *this <=1

            inline bool gtz() const noexcept { return words>0; } //!< \return *this > 0
            inline bool gt1() const noexcept { return !leq1(); } //!< \return *this > 1

            //! make zero
            void ldz() noexcept
            {
                assert(sanity());
                memset(word,0,words*WordBytes);
                Coerce(words) = 0;
                Coerce(bytes) = 0;
                Coerce(bits)  = 0;
                assert(sanity());
            }

            //! zpad when necessary
            inline void zpad() noexcept
            {
                memset(word+words,0,(maxWords-words)*WordBytes);
            }

        private:
            //! set words with no check \param n value
            inline void rawLoad(const natural_t n) noexcept
            {
                assert(maxBytes>=sizeof(n));
                assert(sanity());
                Calculus::SplitWord::Expand(word,n);
                Coerce(bytes) = sizeof(natural_t);
                Coerce(words) = sizeof(natural_t) >> WordShift;
            }

        public:

            //! load a new integral \param n integral to load
            inline void construct( const natural_t n ) noexcept
            {
                rawLoad(n);
                update();
            }

            //! load a new integral and zpad \param n integral to load
            inline void assign(const natural_t n) noexcept
            {
                rawLoad(n);
                zpad();
                update();
            }


            //! \return lowest natural
            inline natural_t getNatural() const noexcept
            {
                assert(sanity());
                natural_t n = 0;
                Calculus::SplitWord::Gather(n,word);
                return n;
            }


            //! check sanity \return true iff zeroed trailing
            inline bool sanity() const noexcept
            {
                return Y_TRUE == Yttrium_Zeroed(word+words,(maxWords-words)*WordBytes);
            }

            //! updated all counts from current words
            inline void update() noexcept
            {
                while(words>0)
                {
                    const size_t   msi = words-1;   // most significant index
                    const WordType msw = word[msi]; // most significant word
                    if(msw<=0) { --Coerce(words); continue; }
                    assert(msw>0);
                    const size_t  xs = msi * WordBytes;
                    Coerce(bytes)    = Calculus::RequiredBytes::For(msw) + xs;
                    Coerce(bits)     = Calculus::RequiredBits::For(msw) + (xs<<3);
                    assert(sanity());
                    return;
                }

                Coerce(bytes) = 0;
                Coerce(bits)  = 0;
                assert(sanity());
            }

            //! hexadecimal string \return upper case representation
            inline String toHex() const
            {
                if(bits<=0)
                {
                    return "0x0";
                }
                else
                {
                    String s;
                    size_t n = 0;
                    for(size_t i=0;i<words;++i)
                    {
                        uint8_t u[WordBytes];
                        Calculus::SplitWord::Expand(u,word[i]);
                        for(size_t j=0;j<WordBytes&&n<bytes;++j,++n)
                        {
                            const uint8_t b = u[j];
                            const uint8_t lo = (uint8_t)(b&0xf); assert(lo<16);
                            const uint8_t up = (uint8_t)(b>>4);  assert(up<16);
                            s += Hexadecimal::UpperChar[lo];
                            s += Hexadecimal::UpperChar[up];
                        }
                        assert(s.size()>0);
                        if(s[s.size()] == '0' ) s.popTail();
                    }
                    return "0x" + s.reverse();
                }
            }

            //! in place right shift a.k.a divide by two \return this
            inline Keg * shr() noexcept
            {
                assert(sanity());

                switch(words)
                {
                    case 0:                           return this;
                    case 1:  word[0] >>= 1; update(); return this;
                    default: break;
                }
                assert(words>=2);
                const size_t msi = words-1;
                for(size_t i=0;i<msi;)
                {
                    WordType &curr = word[i++];
                    curr >>= 1;
                    if(0 != (word[i]&LowerBit)) curr |= UpperBit;
                }
                word[msi] >>= 1;
                update();
                return this;
            }

            //! shl \return multiplied by two
            inline Keg * shl() const
            {
                const size_t n   = words+1;
                Keg *        res = new Keg(WithAtLeast,n);
                {
                    WordType * const target = res->word;
                    for(size_t i=words;i>0;)
                    {
                        const size_t   j = i;
                        const WordType w = word[--i];
                        if( 0 != (w&UpperBit) )
                        {
                            target[j] |= LowerBit;
                        }
                        target[i] = (WordType)(w<<1);
                    }
                }
                Coerce(res->words) = n;
                res->update();
                return res;
            }


            //! get bit \param ibit bit in [0:bits-1] \return boolean value
            inline bool getBit(const size_t ibit) const noexcept
            {
                assert(ibit<bits);
                const size_t q = ibit / WordBits;     assert(q<words);
                const size_t r = ibit - q * WordBits; assert(r<WordBits);
                return ( 0 != (word[q] & BitsData<WORD>::Mask[r]) );
            }

            //! set bit (would need update) \param ibit in [0:maxBits-1]
            inline void setBit(const size_t ibit) noexcept
            {
                assert(ibit<maxBytes*8);
                const size_t q = ibit / WordBits;     assert(q<maxWords);
                const size_t r = ibit - q * WordBits; assert(r<WordBits);
                word[q] |= BitsData<WORD>::Mask[r];
            }

            //! clear bit (would need update) \param ibit in [0:maxBits-1]
            inline void clrBit(size_t ibit) noexcept
            {
                assert(ibit<maxBytes*8);
                const size_t q = ibit / WordBits;     assert(q<maxWords);
                const size_t r = ibit - q * WordBits; assert(r<WordBits);
                word[q] &= BitsData<WORD>::Not2[r];
            }


            //! in-place right shift \param n bits to shift
            inline void shr(const size_t n) noexcept
            {
                if(n>=bits)
                    ldz();
                else
                {
                    const size_t newBits = bits-n;
                    for(size_t i=0,j=n;i<newBits;++i,++j)
                    {
                        if(getBit(j)) setBit(i); else clrBit(i);
                    }
                    for(size_t i=newBits;i<bits;++i) clrBit(i);
                    update();
                }
            }

            //! left shift \param n bits to shift \return new keg with shifted bits
            inline Keg * shl(const size_t n) const
            {
                if(bits<=0)
                    return new Keg();
                else
                {
                    const size_t newBits  = n+bits;
                    const size_t newWords = Alignment::To<WORD>::Ceil(newBits) / sizeof(WORD);
                    Keg * const  res      =  new Keg(WithAtLeast,newWords);

                    for(size_t i=0,j=n;i<bits;++i,++j)
                    {
                        if( getBit(i) ) res->setBit(j);
                    }

                    Coerce(res->words) = newWords;
                    res->update();
                    assert(newBits==res->bits);
                    return res;
                }

            }

            //! make random with exactly nbit
            /**
             \param nbit bits to ste
             \param coin coin to choose bit
             \return new keg with exactly nbit and randon content
             */
            static Keg * MakeRandom( Random::CoinFlip &coin, const size_t nbit)
            {
                if(nbit<=0)
                    return new Keg();
                else
                {
                    const size_t msb = nbit-1;
                    Keg * const  res = new Keg(TwoToThePowerOf,msb);
                    for(size_t i=0;i<msb;++i) {
                        if(coin.heads()) res->setBit(i);
                    }
                    return res;
                }
            }

            //! \return binary version
            inline String toBin() const
            {
                if(words<=0) return "0";
                String res;
                for(size_t i=bits;i>0;)
                {
                    const bool b = getBit(--i);
                    res += (b?'1':'0');
                }
                return res;
            }

            //! \return true iff even number
            inline bool isEven() const noexcept
            {
                assert( sanity() );
                return 0 == (word[0] & LowerBit);
            }

            //! \return true iff odd number
            inline bool isOdd() const noexcept
            {
                assert( sanity() );
                return 0 != (word[0] & LowerBit);
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t     bits;       //!< current bits
            const size_t     bytes;      //!< current bytes
            const size_t     maxBytes;   //!< maxium bytes
            const size_t     words;      //!< current words
            const size_t     maxWords;   //!< capacity in words
            const unsigned   blockShift; //!< maxBytes = 2^blockShift
            WordType * const word;       //!< memory

        private:
            Y_Disable_Assign(Keg); //!< discarded

        };

    }
}



#endif // !Y_Apex_Keg_Included
