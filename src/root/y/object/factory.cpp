
#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/dyadic.hpp"
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
        return Alignment::To<CompressType>::Ceil(blockSize);
    }


    void * Object:: Factory:: query(const size_t blockSize)
    {
        if(blockSize>=MaxVastBytes)
            throw Specific::Exception(CallSign,"blockSize=%s overflow", Decimal(blockSize).c_str() );


        Y_Lock(access);
        const Model model = ModelFor(blockSize);
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
                static Memory::Dyadic & dyadic  = Memory::Dyadic::Instance();
                const unsigned          shift   = CeilLog2(blockSize);
                return dyadic.acquireBlock(shift);
            }
        }
        return 0;
    }

    void Object:: Factory:: store(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(blockSize<=MaxVastBytes);
        
        Y_Lock(access);
        const Model model = ModelFor(blockSize);
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
                static Memory::Dyadic & dyadic  = Memory::Dyadic::Location();
                const unsigned          shift   = CeilLog2(blockSize);
                dyadic.releaseBlock(blockAddr,shift);
            } return;
        }
    }
}

#include "y/memory/allocator/global.hpp"

namespace Yttrium
{

    void * Object:: Factory:: acquire(size_t &blockSize)
    {
        Y_Lock(access);

        if(blockSize<=MaxFairBytes)
        {
            static Memory::Allocator & pooled = Memory::Pooled::Instance();
            return pooled.acquire(blockSize);
        }

        if(blockSize<=MaxVastBytes)
        {
            static Memory::Allocator & dyadic = Memory::Dyadic::Instance();
            return dyadic.acquire(blockSize);
        }
        
        {
            static Memory::Allocator & global = Memory::Global::Instance();
            return global.acquire(blockSize);
        }
    }


    void Object:: Factory:: release(void * & blockAddr, size_t & blockSize) noexcept
    {
        Y_Lock(access);
        if(blockSize<=MaxFairBytes)
        {
            static Memory::Allocator & pooled = Memory::Pooled::Location();
            return pooled.release(blockAddr,blockSize);
        }

        if(blockSize<=MaxVastBytes)
        {
            static Memory::Allocator & dyadic = Memory::Dyadic::Location();
            return dyadic.release(blockAddr,blockSize);
        }

        {
            static Memory::Allocator & global = Memory::Global::Location();
            return global.release(blockAddr,blockSize);
        }
    }


}


