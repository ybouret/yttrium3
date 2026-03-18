//! \file

#ifndef Y_Memory_Sentinel_Included
#define Y_Memory_Sentinel_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //__________________________________________________________________
        //
        //
        //
        //! light-weight sentinel on a memory region
        //
        //
        //__________________________________________________________________
        class Sentinel
        {
        public:
            //! setup
            /**
             \param blockName persistent block name
             \param blockAddr persistent block address
             \param blockSize persistent block size
             */
            Sentinel(const char * const blockName,
                     const void * const blockAddr,
                     const size_t       blockSize) noexcept;

            //! cleanup with checksum check
            ~Sentinel() noexcept;


            const char * const name; //!< persistent name
        private:
            Y_Disable_Copy_And_Assign(Sentinel); //!< discarded
            const void * const addr; //!< original address
            const size_t       size; //!< original size
            const uint32_t     crc;  //!< initial checksum
        };
    }
}
#endif // !Y_Memory_Sentinel_Included

