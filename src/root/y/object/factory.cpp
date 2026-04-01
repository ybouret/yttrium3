
#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/pooled.hpp"

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

    Object:: Factory::Model Object:: Factory:: ModelFor(const size_t blockSize) noexcept
    {
        static const size_t   _1           = 1;
        static const unsigned MaxSlimShift = Memory::Metrics::MinPageShift-1;
        static const size_t   MaxSlimBytes = _1 << MaxSlimShift;
        static const size_t   MaxFairBytes =  Memory::Plastic::Forge::DefaultMaxBlockSize;
        static const size_t   MaxVastBytes = Memory::Metrics::MaxPageBytes;

        if(blockSize<=0)            return None;
        if(blockSize<=MaxSlimBytes) return Slim;
        if(blockSize<=MaxFairBytes) return Fair;
        if(blockSize<=MaxVastBytes) return Vast;
        return Huge;
    }

    size_t Object:: Factory:: SlimCompress(const size_t blockSize) noexcept
    {
        return Alignment::SystemMemory::Ceil(blockSize);
    }


    void * Object:: Factory:: query(const size_t blockSize)
    {
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
            }
        }
    }

}


