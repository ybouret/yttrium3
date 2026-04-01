
#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    const char * const Object::Factory::CallSign = "Object";

    
    Object:: Factory:: ~Factory() noexcept
    {
    }

    Object:: Factory:: Factory() :
    Singleton<Factory,Policy>()
    {
    }


    namespace
    {
        static const size_t   _1           = 1;
        static const unsigned MaxSlimShift = Memory::Metrics::MinPageShift-1;
    }
    const size_t   Object:: Factory:: MaxSlimBytes = _1 << MaxSlimShift;
    const size_t   Object:: Factory:: MaxFairBytes =  Memory::Plastic::Forge::DefaultMaxBlockSize;
    const size_t   Object:: Factory:: MaxVastBytes =  Memory::Metrics::MaxPageBytes;

    Object:: Factory::Model Object:: Factory:: ModelFor(const size_t blockSize) noexcept
    {
        assert(blockSize<=MaxVastBytes);
        if(blockSize<=0)            return None;
        if(blockSize<=MaxSlimBytes) return Slim;
        if(blockSize<=MaxFairBytes) return Fair;
        return Vast;
    }

    size_t Object:: Factory:: SlimCompress(const size_t blockSize) noexcept
    {
        return Alignment::SystemMemory::Ceil(blockSize);
    }


    void * Object:: Factory:: query(const size_t blockSize)
    {
        if(blockSize>=MaxVastBytes) throw Specific::Exception(CallSign,"blockSize=%s overflow", Decimal(blockSize).c_str() );
        const Model model = ModelFor(blockSize);
        Y_Lock(access);
        switch(model)
        {
            case None: break;
            case Slim: {
                static Memory::Small::Blocks &blocks = * Concurrent::Nucleus::Instance().blocks;
                return blocks.acquire( SlimCompress(blockSize) );
            }
            case Fair: {
                static Memory::Pooled & pooled = Memory::Pooled::Instance();
                return pooled.legacyAcquire(blockSize);
            }
            case Vast: {
                static Memory::Archon & archon  = Memory::Archon::Instance();
                const unsigned          shift   = CeilLog2(blockSize);
                return archon.acquireBlock(shift);
            }
        }
        return 0;
    }

    void Object:: Factory:: store(void * const blockAddr, const size_t blockSize) noexcept
    {
        const Model model = ModelFor(blockSize);
        Y_Lock(access);
        switch(model)
        {
            case None: assert(0==blockAddr); return;
            case Slim: assert(0!=blockAddr); {
                static Memory::Small::Blocks &blocks = *Concurrent::Nucleus::Location().blocks;
                blocks.release(blockAddr, SlimCompress(blockSize) );
            } return;

            case Fair: assert(0!=blockAddr); {
                static Memory::Pooled & pooled = Memory::Pooled::Location();
                pooled.legacyRelease(blockAddr);
            } return;

            case Vast: assert(0!=blockAddr); {
                static Memory::Archon & archon  = Memory::Archon::Location();
                const unsigned          shift   = CeilLog2(blockSize);
                archon.releaseBlock(blockAddr,shift);
            } return;
        }
    }

}


