
#include "y/apex/k/overseer.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/libc/block/zero.h"
#include "y/hide.hpp"

namespace Yttrium
{
    namespace Apex
    {
        const char * const Overseer:: CallSign = "Apex::Overseer";

        Overseer:: ~Overseer() noexcept
        {

        }

        Overseer:: Overseer() 
        {
        }

        void * Overseer:: StaticWords[NumStaticWords];


        void * Overseer:: acquireBlock(const unsigned blockShift)
        {
            if(blockShift<=StaticBlockShift)
            {
                static const size_t _1 = 1;
                return Yttrium_BZero(StaticWords, _1 << blockShift);
            }
            else
            {
                static Memory::Archon &archon = Memory::Archon::Instance();
                return archon.acquireBlock(blockShift);
            }
        }

        void  Overseer:: releaseBlock(void * const blockEntry, const unsigned blockShift) noexcept
        {
            assert(blockEntry);
            if(blockShift<=StaticBlockShift)
            {
                assert( blockEntry == Hide::Address(StaticWords) );
            }
            else
            {
                static Memory::Archon &archon = Memory::Archon::Location();
                archon.releaseBlock(blockEntry,blockShift);
            }
        }
    }
}
