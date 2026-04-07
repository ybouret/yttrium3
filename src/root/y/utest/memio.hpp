
//! \file

#ifndef Y_UTest_MemIO_Included
#define Y_UTest_MemIO_Included 1

#include "y/exception.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/zeroed.h"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"
#include <iostream>

#include "y/concurrent/condition.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/thread.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/auto-built.hpp"
#include "y/system/wall-time.hpp"
#include "y/check/crc32.hpp"

namespace Yttrium
{

    namespace UTest
    {

        //! Memory I/O tests
        class MemIO
        {
        public:
            //! block  of anonymous data
            struct Block
            {
                void * addr; //!< address
                size_t size; //!< size in bytes
            };

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            template <typename ALLOC>
            static inline
            void Acquire(ALLOC        & mgr,
                         Core::Rand   & ran,
                         const size_t   maxCount,
                         Block  * const blocks,
                         size_t       & count,
                         const size_t   maxBlockSize)
            {
                while(count<maxCount)
                {
                    Block &b = blocks[count];
                    b.size   = ran.in<size_t>(1,maxBlockSize);
                    b.addr   = mgr.query(b.size);
                    if( !Yttrium_Zeroed(b.addr,b.size))
                        throw Specific::Exception(mgr.callSign(),"block is not zeroed!");
                    Random::FillWith(ran,b.addr,b.size,1);
                    ++count;
                }
            }

            template <typename ALLOC>
            static inline
            void Release(ALLOC        & mgr,
                         const size_t   minCount,
                         Block  * const blocks,
                         size_t       & count) noexcept
            {
                while(count>minCount)
                {
                    Block &b = blocks[--count];
                    mgr.store(b.addr,b.size);
                }
            }

            template <typename CLASS> static inline
            void New(Core::Rand &  ran,
                            const size_t  maxCount,
                            Block * const blocks,
                            size_t &      count,
                            const size_t  maxBlockSize)
            {
                while(count<maxCount)
                {
                    Block &b = blocks[count];
                    b.size   = ran.in<size_t>(1,maxBlockSize);
                    b.addr   = CLASS:: operator new(b.size);
                    if( !Yttrium_Zeroed(b.addr,b.size))
                        throw Specific::Exception("AcquireNew","block is not zeroed!");
                    for(size_t iter=ran.in<size_t>(1,10);iter>0;--iter)
                        Random::FillWith(ran,b.addr,b.size,1);
                    ++count;
                }
            }

            template <typename CLASS> static inline
            void Delete(const size_t  minCount,
                        Block * const blocks,
                        size_t &      count)
            {
                while(count>minCount)
                {
                    Block &b = blocks[--count];
                    CLASS:: operator delete(b.addr,b.size);
                }
            }


#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


        public:
            //__________________________________________________________________
            //
            //
            //! test CLASS::Factory
            /**
             \param maxBlockSize probe in [1:maxBlockSize]
             */
            //
            //__________________________________________________________________
            template <typename CLASS, const size_t NUM_BLOCKS> static inline
            void Test(const size_t maxBlockSize)
            {
                typedef typename CLASS::Factory Factory;
                Factory & F = Factory::Instance();
                std::cerr << "-- Testing " << F.callSign() << " with " << NUM_BLOCKS << " blocks in [1:" << maxBlockSize << "]" << std::endl;
                Block blocks[NUM_BLOCKS];
                Y_BZero(blocks);

                Core::Rand ran;
                size_t count = 0;
                Acquire(F,ran,NUM_BLOCKS,blocks,count,maxBlockSize);
                for(size_t i=16;i>0;--i)
                {
                    Random::Shuffle(ran,blocks,count);
                    Release(F,count/ran.in<size_t>(2,32),blocks,count);
                    Acquire(F,ran,NUM_BLOCKS,blocks,count,maxBlockSize);
                }

                Release(F,0,blocks,count);
                std::cerr << "-- Testing " << F.callSign() << " is done!" << std::endl << std::endl;
            }

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            MemIO();
            ~MemIO() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

        private:

            //! Thead Proc, forward to paralellRun \param args this address
            template <typename CLASS, size_t NUM_THREADS, size_t NUM_BLOCKS>
            static inline void Launch(void * const args)
            {
                assert(args);
                MemIO & self = *static_cast<MemIO *>(args);
                self.parallelRun<CLASS,NUM_THREADS,NUM_BLOCKS>();
            }

            //! perform test in thread
            template <typename CLASS, size_t NUM_THREADS, size_t NUM_BLOCKS>
            inline void parallelRun()
            {
                // initialize
                Block  blocks[NUM_BLOCKS]; Y_BZero(blocks);
                size_t count =0;
                long   seed = 0;

                // synchronize
                mutex.lock();
                assert(ready<NUM_THREADS);
                if(++ready<NUM_THREADS)
                {
                    cond.wait(mutex);
                }
                else
                {
                    cond.broadcast();
                }
                {
                    const uint64_t ticks = System::WallTime::Ticks();
                    const uint32_t crc32 = CRC32::Run(ticks);
                    seed = (long) crc32;
                }
                mutex.unlock();

                // run in parallel
                Core::Rand ran(seed);
                New<CLASS>(ran,NUM_BLOCKS,blocks,count,upper);
                for(unsigned cycle=0;cycle<8;++cycle)
                {
                    Random::Shuffle(ran,blocks,count);
                    Delete<CLASS>(count/ran.in<size_t>(2,32),blocks,count);
                    New<CLASS>(ran,NUM_BLOCKS,blocks,count,upper);
                }
                Delete<CLASS>(0,blocks,count);
            }

        public:

            //! perform test in threads \param maxBlockSize maximum block size to new/delete
            template <size_t NUM_THREADS, typename CLASS, size_t NUM_BLOCKS>
            inline void test(const size_t maxBlockSize)
            {
                std::cerr << "-- Testing Parallel New/Delete with " << NUM_THREADS << " threads" << std::endl;
                static const size_t Required   = NUM_THREADS * sizeof(Concurrent::Thread);
                void *              wksp[ Alignment::WordsGEQ<Required>::Count ];
                ready = 0;
                upper = maxBlockSize;
                Concurrent::Thread::Proc const proc = Launch<CLASS,NUM_THREADS,NUM_BLOCKS>;
                void *  const                  args = this;
                Memory::AutoBuilt<Concurrent::Thread> threads(wksp,NUM_THREADS,proc,args);
                std::cerr << "-- Testing Parallel Done!" << std::endl << std::endl;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Concurrent::Mutex     mutex; //!< mutex
            Concurrent::Condition cond;  //!< condition variable
            size_t                ready; //!< synchronization flag

        private:
            size_t                upper; //!< temporary maxBlockSize
        };

    }

}

#endif // !Y_UTest_MemIO_Included

