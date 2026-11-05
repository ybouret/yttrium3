//! \file

#ifndef Y_Memory_Sentinel_Included
#define Y_Memory_Sentinel_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! light-weight sentinel on a memory region
        //
        //
        //______________________________________________________________________
        class Sentinel
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup for block
            /**
             \param blockAddr persistent block address
             \param blockSize persistent block size
             */
            Sentinel(const void * const blockAddr,
                     const size_t       blockSize) noexcept;


            //! setup for variable \param host variable to watch
            template <typename T> inline
            Sentinel(const T &host) noexcept :
            addr( &host ),
            size( sizeof(T) ),
            crc( chk() )
            {
            }


            //! cleanup with checksum check
            ~Sentinel() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            uint32_t chk()         const noexcept; //!< \return checksum of addr[size]
            bool     wasModified() const noexcept; //!< \return chk() != crc
            bool     isUntouched() const noexcept; //!< \return chk() == crc


        private:
            Y_Disable_Copy_And_Assign(Sentinel); //!< discarded
            const void * const addr; //!< original address
            const size_t       size; //!< original size
            const uint32_t     crc;  //!< initial checksum
        };
    }
}




#endif // !Y_Memory_Sentinel_Included

