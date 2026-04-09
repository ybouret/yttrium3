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

#include <iostream>
#include <cstring>

namespace Yttrium
{
    namespace Apex
    {


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
            inline explicit Keg(const size_t userBytes) :
            bits(0),
            bytes(0),
            maxBytes( Alignment::To<WordType>::Ceil( CheckedBytes(userBytes) ) ),
            words(0),
            maxWords(0),
            blockShift( CeilLog2(maxBytes)  ),
            word( static_cast<WordType *>(AcquireWords( Coerce(blockShift) ) ) )
            {
                Coerce(maxBytes) = size_t(1) << blockShift;
                Coerce(maxWords) = maxBytes >> WordShift;
                assert(maxWords*sizeof(WordType)==maxBytes);
            }

            //! cleanup
            inline virtual ~Keg() noexcept {
                ReleaseWords(word,blockShift);
            }

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

            inline natural_t getNatural() const noexcept
            {
                assert(sanity());
                natural_t n = 0;
                Calculus::SplitWord::Gather(n,word);
                return n;
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

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
            const unsigned   blockShift; //!< maxBytes = 2^blockShify
            WordType * const word;       //!< memory

        private:
            Y_Disable_Copy_And_Assign(Keg); //!< discarded

        };

    }
}



#endif // !Y_Apex_Keg_Included
