
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

    static inline
    void MemoryInThread(void * const args)
    {
        assert(0!=args);
        Lockable         & sync   = Lockable::Giant();
        System::WallTime & chrono = *static_cast<System::WallTime *>(args);
        long               seed   = 0;
        {
            Y_Lock(sync);
            const uint64_t u = System::WallTime::Ticks();
            seed = (long) CRC32::Run(u);
            (std::cerr << "In Thread, seed=" << seed << std::endl).flush();
        }

        Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Location();
        Core::Rand           ran(seed);
        {
            Y_Lock(sync);
            chrono.waitFor(0.01f + ran() * 0.02f);
        }
        Block        blocks[100];
        const size_t nblock = Y_Static_Size(blocks);
        Torture(nucleus,blocks,nblock,ran);

    }

    class MyThread : public Concurrent::Thread
    {
    public:
        explicit MyThread(System::WallTime &chrono) :
        Concurrent::Thread(MemoryInThread,&chrono)
        {
        }

        virtual ~MyThread() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(MyThread);
    };
}

Y_UTEST(concurrent_memory)
{
    const size_t numThreads = 8;
    void *       wksp[ Alignment::WordsGEQ<numThreads*sizeof(MyThread)>::Count ];
    System::WallTime chrono;
    Memory::AutoBuilt<MyThread> threads(wksp,numThreads,chrono);
}
Y_UDONE()

