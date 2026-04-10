
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
            static void * AcquireWords(unsigned &blockShift);                  //!< \param blockShift input and modified \return valid block
            static void   ReleaseWords(void * const, const unsigned) noexcept; //!< releases acquired block

        private:
            Y_Disable_Copy_And_Assign(KegMetrics); //!< discarded
        };

    }

}

#endif // !Y_Apex_KegMetrics_Included

