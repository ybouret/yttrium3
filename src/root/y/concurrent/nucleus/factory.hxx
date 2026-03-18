#include "y/memory/metrics.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        Memory::Page * Nucleus:: acquirePage(const unsigned shift)
        {
            static const char fn[] = "Nucleus::acquirePage";
            assert(shift>=Memory::Metrics::MinPageShift);
            assert(shift<=Memory::Metrics::MaxPageShift);
            assert(code);

            // allocating
            Y_Lock(access);
            const size_t blockSize = size_t(1) << shift;
            void * const blockAddr = calloc(1,blockSize);
            if(!blockAddr)
                throw Libc::Exception(ENOMEM,"%s(2^%u)",fn,shift);

            assert( Yttrium_Zeroed(blockAddr,blockSize) );

            // updating
            Code::RAM += blockSize;
            Memory::Page * const page = static_cast<Memory::Page *>(blockAddr);
            assert(0==page->next);
            assert(0==page->prev);
            return page;
        }


        void Nucleus:: releasePage(Memory::Page *const page, const unsigned int shift) noexcept
        {
            assert(0!=page);
            assert(shift>=Memory::Metrics::MinPageShift);
            assert(shift<=Memory::Metrics::MaxPageShift);

            Y_Lock(access);
            const size_t blockSize = size_t(1) << shift; assert(Code::RAM>=blockSize);
            Code::RAM -= blockSize;
            free(page);
        }


    }

}
