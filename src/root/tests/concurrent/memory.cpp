
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/auto-built.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/rand.hpp"
#include "y/check/crc32.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"
#include "y/libc/block/zeroed.h"
#include "y/memory/pages.hpp"
#include "y/memory/book.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/global.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/allocator/archon.hpp"

using namespace Yttrium;



namespace
{
    struct Block
    {
        void * addr;
        size_t size;
        void fill(Core::Rand &ran) noexcept
        {
            Random::FillWith(ran,addr,size,1);
        }
    };

    struct Wad
    {
        void *   entry;
        unsigned shift;
    };

    static inline
    void Acquire(Memory::Allocator & alloc,
                 const size_t        nmax,
                 Block               blocks[],
                 size_t            & count,
                 Core::Rand        & ran)
    {
        while(count<nmax)
        {
            Block &b = blocks[count];
            b.size   = ran.in<size_t>(0,1000);
            b.addr   = alloc.acquire(b.size);
            Y_ASSERT( Y_TRUE == Yttrium_Zeroed(b.addr,b.size) );
            b.fill(ran);
            ++count;
        }
    }

    static inline
    void Release(Memory::Allocator &alloc,
                 const size_t       nmin,
                 Block              blocks[],
                 size_t            &count) noexcept
    {
        while(count>nmin)
        {
            Block &b = blocks[--count];
            alloc.release(b.addr,b.size);
        }
    }

    static inline
    void Torture(Memory::Allocator &alloc,
                 Block               blocks[],
                 const size_t        nblock,
                 Core::Rand         &ran)
    {
        size_t count = 0;
        Acquire(alloc,nblock,blocks,count,ran);
        for(size_t iter=ran.in<size_t>(10,100);iter>0;--iter)
        {
            Random::Shuffle(ran,blocks,nblock);
            Release(alloc,nblock/ran.in<size_t>(2,4),blocks,count);
            Acquire(alloc,nblock,blocks,count,ran);
        }
        Release(alloc,0,blocks,count);
    }

}

namespace {
    static inline
    void Acquire(Memory::Book &book,
                 const size_t nmax,
                 Wad          wads[],
                 size_t      &count,
                 Core::Rand &ran)
    {
        while(count<nmax)
        {
            Wad &wad = wads[count];
            wad.shift = ran.in<unsigned>(8,14);
            wad.entry = book[wad.shift].get();
            ++count;
        }
    }

    static inline void Release(Memory::Book &book,
                               const size_t nmin,
                               Wad          wads[],
                               size_t &     count) noexcept
    {
        while(count>nmin)
        {
            Wad &wad = wads[--count];
            book[wad.shift].put(wad.entry);
        }
    }

    static inline
    void Torture(Memory::Book &book,
                 Wad           wads[],
                 const size_t  nwad,
                 Core::Rand   &ran)
    {
        size_t count = 0;
        Acquire(book,nwad,wads,count,ran);
        for(size_t iter=ran.in<size_t>(10,100);iter>0;--iter)
        {
            Random::Shuffle(ran,wads,nwad);
            Release(book,nwad/ran.in<size_t>(2,4),wads,count);
            Acquire(book,nwad,wads,count,ran);
        }
        Release(book,0,wads,count);
    }

}

namespace
{
    static inline
    void Acquire(Memory::Small::Blocks & alloc,
                 const size_t        nmax,
                 Block               blocks[],
                 size_t            & count,
                 Core::Rand        & ran)
    {
        while(count<nmax)
        {
            Block &b = blocks[count];
            b.size   = ran.in<size_t>(1,500);
            b.addr   = alloc.acquire(b.size);
            Y_ASSERT( Y_TRUE == Yttrium_Zeroed(b.addr,b.size) );
            b.fill(ran);
            ++count;
        }
    }

    static inline
    void Release(Memory::Small::Blocks &alloc,
                 const size_t       nmin,
                 Block              blocks[],
                 size_t            &count) noexcept
    {
        while(count>nmin)
        {
            Block &b = blocks[--count];
            alloc.release(b.addr,b.size);
            Y_VZero(b);
        }
    }

    static inline
    void Torture(Memory::Small::Blocks &alloc,
                 Block                  blocks[],
                 const size_t           nblock,
                 Core::Rand            &ran)
    {
        size_t count = 0;
        Acquire(alloc,nblock,blocks,count,ran);
        for(size_t iter=ran.in<size_t>(10,100);iter>0;--iter)
        {
            Random::Shuffle(ran,blocks,nblock);
            Release(alloc,nblock/ran.in<size_t>(2,4),blocks,count);
            Acquire(alloc,nblock,blocks,count,ran);
        }
        Release(alloc,0,blocks,count);
    }
}


namespace {

    struct Params
    {
        System::WallTime      * chrono;
        Concurrent::Nucleus   * nucleus;
        Memory::Allocator     * global;
        Memory::Allocator     * pooled;
        Memory::Allocator     * dyadic;
        Memory::Allocator     * archon;
    };

    static inline
    void MemoryInThread(void * const args)
    {
        assert(0!=args);
        Lockable              & sync    = Lockable::Giant();
        Params                & params  = *static_cast<Params *>(args);
        long                    seed    = 0;
        {
            Y_Lock(sync);
            const uint64_t u = System::WallTime::Ticks();
            seed = (long) CRC32::Run(u);
            (std::cerr << "In Thread, seed=" << seed << std::endl).flush();
        }

        Core::Rand ran(seed);
        Block      blocks[512];
        Wad        wads[512];

        Torture(*params.nucleus,         blocks, Y_Static_Size(blocks), ran);
        Torture( params.nucleus->book,   wads,   Y_Static_Size(wads),   ran);
        Torture(*params.nucleus->blocks, blocks, Y_Static_Size(blocks), ran);
        Torture(*params.global,          blocks, Y_Static_Size(blocks), ran);
        Torture(*params.pooled,          blocks, Y_Static_Size(blocks), ran);
        Torture(*params.dyadic,          blocks, Y_Static_Size(blocks), ran);
        Torture(*params.archon,          blocks, Y_Static_Size(blocks), ran);

    }

    class MyThread : public Concurrent::Thread
    {
    public:

        explicit MyThread(Params &params) : Concurrent::Thread(MemoryInThread,&params)
        {
        }

        virtual ~MyThread() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(MyThread);
    };
}

#include "y/stream/xmlog.hpp"

Y_UTEST(concurrent_memory)
{
    Concurrent::Singulet::Verbose = true;
    System::WallTime        chrono;
    Concurrent::Nucleus   & nucleus = Concurrent::Nucleus::Location();

    Params params = {
        &chrono,
        &nucleus,
        & Memory::Global::Instance(),
        & Memory::Pooled::Instance(),
        & Memory::Dyadic::Instance(),
        & Memory::Archon::Instance()
    };

    {
        const size_t numThreads = 8;
        void *       wksp[ Alignment::WordsGEQ<numThreads*sizeof(MyThread)>::Count ];
        Memory::AutoBuilt<MyThread> threads(wksp,numThreads,params);
    }

    //bool verbose = true;
    //XML::Log xml(std::cerr,verbose);
    //nucleus.toXML(xml);
}
Y_UDONE()

