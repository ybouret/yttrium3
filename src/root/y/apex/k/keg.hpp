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

#include "y/string.hpp"

#include <iostream>
#include <cstring>

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
            typedef WORD           WordType;                                   //!< storage type
            static  const size_t   WordBytes = sizeof(WordType);              //!< alias
            static  const unsigned WordShift = IntegerLog2<WordBytes>::Value; //!< alias
            static  const size_t   WordBits  = WordBytes * 8;                 //!< alias



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

            inline explicit Keg(const CopyOf_ &, const natural_t n) :
            bits(0),
            bytes(0),
            maxBytes(0),
            words(0),
            Y_Apex_Keg_Alloc()
            {
                ld(n);
            }

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

            inline explicit Keg(const WithAtLeast_ &, const size_t numWords) :
            bits(0),
            bytes(0),
            maxBytes( CheckedBytes(numWords*WordBytes) ),
            words(0),
            Y_Apex_Keg_Alloc()
            {
                assert(maxWords>=numWords);
            }



            //! cleanup
            inline virtual ~Keg() noexcept { ReleaseWords(word,blockShift); }

            //! display
            inline friend std::ostream & operator<<( std::ostream &os, const Keg &keg)
            {
                Hexadecimal::Display(os,keg.word,keg.words);
                os << "#bits=" << keg.bits << "|bytes=" << keg.bytes;
                if(WordBytes>1) os << "|words=" << keg.words;
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            inline void zpad() noexcept
            {
                memset(word+words,0,(maxWords-words)*WordBytes);
            }

            //! load a new integral \param n integral to load
            inline void ld( const natural_t n ) noexcept
            {
                assert(maxBytes>=sizeof(n));
                Calculus::SplitWord::Expand(word,n);
                Coerce(bytes) = sizeof(natural_t);
                Coerce(words) = sizeof(natural_t) >> WordShift;
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

            inline String toHex() const
            {
                if(bits<=0)
                {
                    return "0x00";
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
                            const uint8_t lo = (b&0xf); assert(lo<16);
                            const uint8_t up = b>>4;    assert(up<16);
                            s += Hexadecimal::UpperChar[lo];
                            s += Hexadecimal::UpperChar[up];
                        }
                        assert(s.size()>0);
                        if(s[s.size()] == '0' ) s.popTail();
                    }
                    return "0x" + s.reverse();
                }
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
