#include "y/core/htable.hpp"
#include "y/exception.hpp"
#include "y/calculus/base2.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/core/max.hpp"

#include <iostream>

namespace Yttrium
{

    namespace Core
    {
        const char * const HTable:: CallSign = "Core::HTable";

        static inline unsigned HTableShift(size_t minSlots, const size_t bytesPerSlot)
        {
            assert(bytesPerSlot>0);
            minSlots = Max<size_t>(HTable::MinSlots,minSlots);
            const size_t   maxSlots = Base2<size_t>::MaxBytes / bytesPerSlot;
            if(minSlots>maxSlots)
                throw Specific::Exception(HTable::CallSign,"too many required slots");
            const size_t   bytes =  minSlots * bytesPerSlot;
            return Max<unsigned>(Memory::Archon::MinBlockShift,CeilLog2(bytes));
        }

        static inline void * HTableAcquire(const unsigned blockShift)
        {
            static Memory::Archon &archon = Memory::Archon::Instance();
            return archon.acquireBlock(blockShift);
        }

        HTable:: HTable(const size_t minSlots, const size_t bytesPerSlot) :
        tsize(minSlots),
        tmask(0),
        shift( HTableShift(minSlots,bytesPerSlot) ),
        entry( HTableAcquire(shift) )
        {
            static const size_t one = 1;
            const size_t        bytes    = one<<shift;
            const size_t        maxCount = bytes/bytesPerSlot;
            Coerce(tsize) = PrevPowerOfTwo(maxCount);
            Coerce(tmask) = tsize-1;
            assert(tsize>=minSlots);
        }

        HTable:: ~HTable() noexcept
        {
            static Memory::Archon &archon = Memory::Archon::Location();
            assert(entry);
            assert(tsize);
            assert(shift);
            archon.releaseBlock(entry,shift);
            Coerce(entry) = 0;
            Coerce(tsize) = 0;
            Coerce(tmask) = 0;
            Coerce(shift) = 0;
        }

    }

}
