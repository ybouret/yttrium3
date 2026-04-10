
//! \file

#ifndef Y_Apex_KegMetrics_Included
#define Y_Apex_KegMetrics_Included 1

#include "y/object/light.hpp"
#include "y/memory/metrics.hpp"


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
            static const size_t       MaxBytes = Memory::Metrics::MaxPageBytes; //!< alias
            static const char * const CallSign; //!< "Apex"

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
            static size_t CheckedBytes(const size_t);                            //!< \return checked bytes, exception upon error
            static void   ReleaseWords(void * const, const unsigned) noexcept; //!< releases acquired block

            static void * AcquireBytes(unsigned &blockShift,
                                       size_t   &maxBytes);

            template <typename WORD>
            static inline WORD * AcquireWords(unsigned &blockShift,
                                              size_t   &maxBytes,
                                              size_t   &maxWords)
            {
                WORD * const w = static_cast<WORD *>( AcquireBytes(blockShift,maxBytes) );
                maxWords = maxBytes / sizeof(WORD);
                return w;
            }

        private:
            Y_Disable_Copy_And_Assign(KegMetrics); //!< discarded
        };

    }

}

#endif // !Y_Apex_KegMetrics_Included

