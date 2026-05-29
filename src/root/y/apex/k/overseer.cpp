
#include "y/apex/k/overseer.hpp"
#include "y/memory/allocator/archon.hpp"
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


        void * Overseer:: get(const unsigned blockShift)
        {
            if(blockShift<=StaticBlockShift)
            {
                static void * const entry = Hide::Address(StaticWords);
                // TODO: check if need to zero...
                return entry;
            }
            else
            {
                static Memory::Archon &archon = Memory::Archon::Instance();
                return archon.acquireBlock(blockShift);
            }
        }

        void  Overseer:: put(void * const blockEntry, const unsigned blockShift) noexcept
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
