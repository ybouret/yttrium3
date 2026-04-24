//! \file

#ifndef Y_Memory_Classified_Included
#define Y_Memory_Classified_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/zeroed.h"
#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        template <typename T, typename ALLOCATOR>
        class Classified : public Memory::ReadWriteBuffer
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit Classified(const size_t numBlocks) :
            space(numBlocks),
            count(numBlocks),
            bytes(0),
            entry( AcquireMem(count,bytes) )
            {
                assert(count>=space);
                assert( Y_TRUE == Yttrium_Zeroed(entry,bytes) );
            }
            

            inline virtual ~Classified() noexcept
            {
                static ALLOCATOR & mgr = ALLOCATOR::Location();
                mgr.releaseAs(entry,count,bytes);
                Coerce(space) = 0;
            }

            virtual const void * ro()     const noexcept { return entry; }
            virtual size_t       length() const noexcept { return bytes; }

            MutableType * operator()(const size_t indx) noexcept
            {
                assert(indx<space);
                return entry+indx;
            }

            ConstType * operator()(const size_t indx) const noexcept
            {
                assert(indx<space);
                return entry+indx;
            }


            const size_t space;
        private:
            Y_Disable_Copy_And_Assign(Classified);
            size_t        count;
            size_t        bytes;
            MutableType * entry;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline MutableType * AcquireMem(size_t &numItems, size_t &numBytes)
            {
                static ALLOCATOR & mgr = ALLOCATOR::Instance();
                return mgr.template acquireAs<MutableType>(numItems,numBytes);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Memory_Classified_Included

