
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/threaded.hpp"
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
#include "y/format/hexadecimal.hpp"

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
    void Torture(Memory::Allocator &  alloc,
                 Block                blocks[],
                 const size_t         nblock,
                 Core::Rand         & ran)
    {
        Yttrium_BZero(blocks,nblock*sizeof(Block));

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
    void Torture(Memory::Small::Blocks & alloc,
                 Block                   blocks[],
                 const size_t            nblock,
                 Core::Rand            & ran)
    {
        size_t count = 0;
        Acquire(alloc,nblock,blocks,count,ran);
        for(size_t iter=ran.in<size_t>(10,100);iter>0;--iter)
        {
            Random::Shuffle(ran,blocks,nblock);
            Release(alloc,nblock/ran.in<size_t>(2,16),blocks,count);
            Acquire(alloc,nblock,blocks,count,ran);
        }
        Release(alloc,0,blocks,count);
    }
}


namespace {

    struct Params
    {
        Concurrent::Nucleus   * nucleus;
        Concurrent::Mutex     * mutex;
        Concurrent::Condition * cv;
        Memory::Allocator     * global;
        Memory::Allocator     * pooled;
        Memory::Allocator     * dyadic;
        Memory::Allocator     * archon;
        size_t                  ready;
    };

#define NUM_THREADS 8
#define NUM_BLOCKS  1024

    static inline
    void synchronize(const char * const     msg,
                     Concurrent::Condition &cv,
                     Concurrent::Mutex     &mutex,
                     size_t                &ready)
    {
        mutex.lock();
        if(++ready>=NUM_THREADS)
        {
            (std::cerr << "-- " << msg << std::endl).flush();
            cv.broadcast();
        }
        else
        {
            cv.wait(mutex);
            ready = 0;
        }
        mutex.unlock();
    }


    static inline
    void MemoryInThread(void * const args)
    {
        assert(0!=args);
        Lockable              & sync    = Lockable::Giant();
        Params                & params  = *static_cast<Params *>(args);
        Concurrent::Mutex     & mutex   = *params.mutex;
        Concurrent::Condition & cv      = *params.cv;
        size_t                & ready   = params.ready;
        long                    seed    = 0;
        {
            Y_Lock(sync);
            const uint64_t u = System::WallTime::Ticks();
            const uint32_t c = CRC32::Run(u);
            seed = (long)c;
            (std::cerr << "In Thread, seed=" << Hexadecimal(c) << std::endl).flush();
        }

        // synchronizing

        Core::Rand ran(seed);
        Block      blocks[NUM_BLOCKS];

#if 0
        synchronize("synchronized for nucleus",cv,mutex,ready);
        Torture(*params.nucleus,blocks,Y_Static_Size(blocks),ran);

        Wad        wads[NUM_BLOCKS];
        synchronize("synchronized for book",cv,mutex,ready);
        Torture( params.nucleus->book,wads,Y_Static_Size(wads),ran);

        synchronize("synchronized for small::blocks",cv,mutex,ready);
        Torture(*params.nucleus->blocks,blocks,Y_Static_Size(blocks),ran);

        synchronize("synchronized for global",cv,mutex,ready);
        Torture(*params.global,blocks,Y_Static_Size(blocks),ran);

        synchronize("synchronized for pooled",cv,mutex,ready);
        Torture(*params.pooled,blocks,Y_Static_Size(blocks),ran);
#endif

        synchronize("synchronized for dyadic",cv,mutex,ready);
        Torture(*params.dyadic,          blocks, Y_Static_Size(blocks), ran);
        //Torture(*params.archon,          blocks, Y_Static_Size(blocks), ran);

        synchronize("returning\n",cv,mutex,ready);
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
    Concurrent::Nucleus   & nucleus = Concurrent::Nucleus::Instance();
    Concurrent::Mutex       mutex;
    Concurrent::Condition   cv;

    Params params = {
        & nucleus,
        & mutex,
        & cv,
        & Memory::Global::Instance(),
        & Memory::Pooled::Instance(),
        & Memory::Dyadic::Instance(),
        & Memory::Archon::Instance(),
        0
    };

    const size_t numThreads = NUM_THREADS;
    void *       wksp[ Alignment::WordsGEQ<numThreads*sizeof(MyThread)>::Count ];

    for(size_t cycle=1;cycle<=2;++cycle)
    {
        (std::cerr << "-- cycle " << cycle << std::endl).flush();
        params.ready = 0;
        Memory::AutoBuilt<MyThread> threads(Y_BZero(wksp),numThreads,params);
    }


}
Y_UDONE()

