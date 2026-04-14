

//! \file

#ifndef Y_Memory_AllocatedBuffer_Included
#define Y_Memory_AllocatedBuffer_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/zeroed.h"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Allocated Buffer
        //
        //
        //______________________________________________________________________
        template <typename ALLOCATOR>
        class AllocatedBuffer : public ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param request minimal size
            inline explicit AllocatedBuffer(const size_t request) noexcept :
            ReadWriteBuffer(),
            size(request),
            addr( AcquireMem(size) )
            {
                assert( Y_TRUE == Yttrium_Zeroed(addr,size) );
            }

            //! cleanup
            inline virtual ~AllocatedBuffer() noexcept
            {
                static ALLOCATOR & mgr = ALLOCATOR::Location();
                Yttrium_BZero(addr,size);
                mgr.release(addr,size);
                assert(!addr);
                assert(!size);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual const void * ro()     const noexcept { return addr; }
            inline virtual size_t       length() const noexcept { return size;    }

            //__________________________________________________________________
            //
            //
            // Member
            //
            //__________________________________________________________________
        private:
            Y_Disable_Copy_And_Assign(AllocatedBuffer); //!< discarded
            size_t size; //!< allocated bytes
            void * addr; //!< allocated address

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline void * AcquireMem(size_t &capa)
            {
                static ALLOCATOR & mgr = ALLOCATOR::Instance();
                return mgr.acquire(capa);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            
        };


    }

}

#endif // !Y_Memory_AllocatedBuffer_Included
