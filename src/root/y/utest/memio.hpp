
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

namespace Yttrium
{

    namespace UTest
    {

        struct MemIO
        {
            struct Block
            {
                void * addr;
                size_t size;
            };

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
                    b.addr   = mgr.acquire(b.size);
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
                    mgr.release(b.addr,b.size);
                }
            }




            template <typename CLASS, const size_t NUM_BLOCKS, const size_t CYCLES=16> static inline
            void Test(Core::Rand &ran, const size_t maxBlockSize)
            {
                typedef typename CLASS::Factory Factory;
                Factory & F = Factory::Instance();
                std::cerr << "-- Testing " << F.callSign() << " with " << NUM_BLOCKS << " blocks in [1:" << maxBlockSize << "], CYCLES=" << CYCLES << std::endl;
                Block blocks[NUM_BLOCKS];
                Y_BZero(blocks);

                size_t count = 0;
                Acquire(F,ran,NUM_BLOCKS,blocks,count,maxBlockSize);
                for(size_t i=CYCLES;i>0;--i)
                {
                    Random::Shuffle(ran,blocks,NUM_BLOCKS);
                    Release(F,count/ran.in<size_t>(2,32),blocks,count);
                    Acquire(F,ran,NUM_BLOCKS,blocks,count,maxBlockSize);
                }

                Release(F,0,blocks,count);
                std::cerr << "-- Testing " << F.callSign() << " is done!" << std::endl << std::endl;

            }
        };

    }

}

#endif // !Y_UTest_MemIO_Included

