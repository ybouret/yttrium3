
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/auto-built.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/rand.hpp"
#include "y/check/crc32.hpp"

using namespace Yttrium;



namespace
{
    struct Block
    {
        void * addr;
        size_t size;
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
        size_t       count  = 0;

        Acquire(nucleus,nblock,blocks,count,ran);

        Release(nucleus,0,blocks,count);
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
    const size_t numThreads = 2;
    void *       wksp[ Alignment::WordsGEQ<numThreads*sizeof(MyThread)>::Count ];
    System::WallTime chrono;
    Memory::AutoBuilt<MyThread> threads(wksp,numThreads,chrono);
}
Y_UDONE()

