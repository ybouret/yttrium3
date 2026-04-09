#include "y/apex/k/metrics.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/core/max.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const KegMetrics:: CallSign = "Apex";

        KegMetrics:: KegMetrics() noexcept
        {
        }


        KegMetrics:: ~KegMetrics() noexcept
        {
        }


        size_t KegMetrics:: CheckedBytes(const size_t userBytes)
        {
            if(userBytes>Memory::Archon::MaxBlockBytes)
                throw Specific::Exception(CallSign, "user bytes overflow");

            return userBytes;
        }

        void * KegMetrics:: AcquireWords(unsigned &blockShift)
        {
            static Memory::Archon & mgr = Memory::Archon::Instance();
            if(InSituMax(blockShift,Memory::Archon::MinBlockShift)>Memory::Archon::MaxBlockShift)
                throw Specific::Exception(CallSign,"blockShift=%u exceeds %u", blockShift, Memory::Archon::MaxBlockShift);
            return mgr.acquireBlock(blockShift);
        }

        void KegMetrics:: ReleaseWords(void * const blockAddr, const unsigned blockShift) noexcept
        {
            static Memory::Archon & mgr = Memory::Archon::Location();
            assert(blockAddr);
            assert(blockShift>=Memory::Archon::MinBlockShift);
            assert(blockShift<=Memory::Archon::MaxBlockShift);
            mgr.releaseBlock(blockAddr,blockShift);
        }

    }

}

