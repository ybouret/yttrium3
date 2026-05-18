//! \file

#ifndef Y_Core_HTable_Included
#define Y_Core_HTable_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{

    namespace Core
    {

        class HTable
        {
        public:
            static const char * const CallSign; //!< "Core::HTable"
            static const size_t       MinSlots = 8;

            explicit HTable(const size_t minSlots, const size_t bytesPerSlot);
            virtual ~HTable() noexcept;

            const size_t   tsize; //!< power of two number of slots
            const size_t   tmask; //!< x%count = x&hmask;
            const unsigned shift;
        protected:
            void * const   entry;

            Y_Disable_Copy_And_Assign(HTable);
        };

    }

}

#endif // !Y_Core_HTable_Included
