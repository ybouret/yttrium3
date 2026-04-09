//! \file

#ifndef Y_Apex_Keg_Included
#define Y_Apex_Keg_Included 1

#include "y/object/light.hpp"
#include "y/memory/metrics.hpp"
#include "y/calculus/alignment.hpp"
#include "y/apex/types.hpp"
#include "y/calculus/required-bits.hpp"
#include "y/calculus/required-bytes.hpp"
#include "y/calculus/split-word.hpp"
#include "y/format/hexadecimal.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Common Metrics for Keg
        //
        //
        //______________________________________________________________________
        class KegMetrics : public LightObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t MaxBytes = Memory::Metrics::MaxPageBytes; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit KegMetrics() noexcept; //!< setup
            virtual ~KegMetrics() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static size_t CheckBytes(const size_t);                            //!< \return checked bytes, exception upon error
            static void * AcquireWords(unsigned &blockShift);                  //!< \param blockShift input and modified \return valid block
            static void   ReleaseWords(void * const, const unsigned) noexcept; //!< releases acquired block

        private:
            Y_Disable_Copy_And_Assign(KegMetrics); //!< discarded
        };

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

#if 0
            static inline size_t WordsFor(const size_t numBytes) noexcept
            {
                Alignment::To<WordType>::Ceil(numBytes) >> WordShift;
            }
#endif

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
            maxBytes( Alignment::To<WordType>::Ceil( CheckBytes(userBytes) ) ),
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
                os << "#bits=" << keg.bits << "|bytes=" << keg.bytes << "|words=" << keg.words;
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! load a new integral \param n integral to load
            inline void ld( const natural_t n ) noexcept
            {
                assert(maxBytes>=sizeof(n));
                Calculus::SplitWord::Expand(word,n);
                Coerce(bytes) = sizeof(natural_t);
                Coerce(words) = sizeof(natural_t) >> WordShift;
                update();
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

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
                    return;
                }

                Coerce(bytes) = 0;
                Coerce(bits)  = 0;
                word[0]       = 0;
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
