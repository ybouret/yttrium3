//! \file

#ifndef Y_Core_HTable_Included
#define Y_Core_HTable_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{

    namespace Core
    {

        //______________________________________________________________________
        //
        //
        //
        //! Memory and metrics for Hash Table based containers
        //
        //
        //______________________________________________________________________
        class HTable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;     //!< "Core::HTable"
            static const size_t       MinSlots = 8; //!< alias
            static const size_t       MaxLoad  = 4; //!< max load factor

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param minSlots minimum number of slots (will be >= MinSlots)
             \param bytesPerSlot size of each slot
             */
            explicit HTable(const size_t minSlots, const size_t bytesPerSlot);
            virtual ~HTable() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t   tsize; //!< power of two number of slots
            const size_t   tmask; //!< for fast modulo
            const unsigned shift; //!< inner memory = 2^shift bytes
        protected:
            void * const   entry; //!< location of slots

            Y_Disable_Copy_And_Assign(HTable); //!< discarded
        };

    }

}

#endif // !Y_Core_HTable_Included
