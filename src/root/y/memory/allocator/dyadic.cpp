#include "y/memory/allocator/dyadic.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/book.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Memory
    {
        const char * const Dyadic:: CallSign = "Memory::Dyadic";

        class Dyadic:: Code
        {
        public:
            static const size_t   MinPageBytes = Metrics::MinPageBytes;
            static const unsigned MinPageShift = Metrics::MinPageShift;
            static const unsigned MaxCommShift = MinPageShift - 1;
            static const size_t   MaxCommBytes = size_t(1) << MaxCommShift;
            static const unsigned NumSmall     = MaxCommShift+1;
            typedef  Small::Arena Arena;
            typedef Arena *       ArenaPtr;

            inline Code(Concurrent::Nucleus &nucleus) :
            dyadicArena(),
            smallBlocks(*nucleus.blocks),
            book(nucleus.book)
            {
                std::cerr << "+" << CallSign << "::Code" << std::endl;
                Y_BZero(dyadicArena);
                std::cerr << "NumSmall=" << NumSmall << std::endl;
            }

            inline ~Code() noexcept
            {
                std::cerr << "~" << CallSign << "::Code" << std::endl;
            }

            inline void * acquire(const unsigned shift)
            {
                static const size_t _1 = 1;

                if(shift<=MaxCommShift)
                {
                    ArenaPtr & pArena = dyadicArena[shift];
                    if(0==pArena)
                        pArena = &smallBlocks[_1<<shift];

                    assert(0!=pArena);
                    assert((_1<<shift) == pArena->blockSize);

                    return pArena->acquire();
                }
                else
                {
                    return book[shift].get();
                }
            }

            inline void release(void * blockAddr, const unsigned shift) noexcept
            {
                if(shift<=MaxCommShift)
                {
                    assert(0!=dyadicArena[shift]);
                    dyadicArena[shift]->release(blockAddr);
                }
                else
                {
                    book[shift].put(blockAddr);
                }
            }

            ArenaPtr                dyadicArena[NumSmall];
            Memory::Small::Blocks & smallBlocks;
            Memory::Book          & book;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            static void *         CodeWksp[ Alignment::WordsFor<Dyadic::Code>::Count ];
            static Dyadic::Code * code = 0;
        }

        Dyadic :: Dyadic() : Singleton<Dyadic,Policy>()
        {
            std::cerr << "sizeof(Code)=" << sizeof(Code) << std::endl;
            assert(0==code);
            code = new ( Y_BZero(CodeWksp) ) Code(Concurrent::Nucleus::Location());
        }

        Dyadic:: ~Dyadic() noexcept
        {
            assert(0!=code);
            Destruct(code);
            code = 0;
            Y_BZero(CodeWksp);
        }

        void * Dyadic:: acquire(size_t &blockSize)
        {
            assert(0!=code);

            if(blockSize>Base2<size_t>::MaxBytes)
                throw Specific::Exception(CallSign,"blockSize overflow");

            Y_Lock(access);
            try
            {
                static const size_t _1        = 1;
                const unsigned      shift     = CeilLog2(blockSize);
                void * const        blockAddr = code->acquire(shift);
                blockSize = _1 << shift;
                return blockAddr;
            }
            catch(...)
            {
                blockSize = 0;
                throw;
            }
        }

        void Dyadic:: release(void * & blockAddr, size_t & blockSize) noexcept
        {
            assert( 0 != code);
            assert( 0 != blockAddr );
            assert( IsPowerOfTwo(blockSize) );

            const unsigned shift = ExactLog2(blockSize);
            Y_Lock(access);
            code->release(blockAddr,shift);
            blockAddr = 0;
            blockSize = 0;
        }
    }
}
