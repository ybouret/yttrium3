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

        //----------------------------------------------------------------------
        //
        //
        //
        // encapsulated code
        //
        //
        //
        //----------------------------------------------------------------------
        class Dyadic:: Code
        {
        public:
            //------------------------------------------------------------------
            //
            //
            // Definitions
            //
            //
            //------------------------------------------------------------------
            static const size_t   _1           = 1;                     //!< alias
            static const size_t   MinPageBytes = Metrics::MinPageBytes; //!< sent to book
            static const unsigned MinPageShift = Metrics::MinPageShift; //!< sent to book
            static const unsigned MaxCommShift = MinPageShift - 1;      //!< sent to arena
            static const size_t   MaxCommBytes = _1 << MaxCommShift;    //!< sent to arena
            static const unsigned NumSmall     = MaxCommShift+1;        //!< auxiliary arenas
            typedef Small::Arena  Arena;    //!< alias
            typedef Arena *       ArenaPtr; //!< alias

            //------------------------------------------------------------------
            //
            //
            // C++
            //
            //
            //------------------------------------------------------------------

            //! setup \param nucleus Nucleus instance
            inline Code(Concurrent::Nucleus &nucleus) :
            dyadicArena(),
            smallBlocks(*nucleus.blocks),
            book(nucleus.book)
            {
                Y_BZero(dyadicArena);
                assert(0!=nucleus.blocks);
                std::cerr << "Dyadic MaxCommBytes=" << MaxCommBytes << std::endl;
            }

            //! cleanup
            inline ~Code() noexcept
            {
            }

            //------------------------------------------------------------------
            //
            //
            // Methods
            //
            //
            //------------------------------------------------------------------
            inline void * acquire(const unsigned blockShift)
            {

                if(blockShift<=MaxCommShift)
                {
                    ArenaPtr &   pArena = dyadicArena[blockShift];
                    if(0==pArena)
                    {
                        const size_t blockSize = _1<<blockShift;
                        smallBlocks.fetch(pArena,blockSize);
                    }

                    assert(0!=pArena);
                    assert(0!=dyadicArena[blockShift]);
                    assert(dyadicArena[blockShift] == pArena);
                    assert( (_1<<blockShift) == pArena->blockSize);

                    return pArena->acquire();
                }
                else
                {
                    assert(blockShift>MaxCommShift);
                    return book[blockShift].get();
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
            // sanity check
            assert(0!=code);
            if(blockSize>Base2<size_t>::MaxBytes)
                throw Specific::Exception(CallSign,"blockSize overflow");

            // locked acquire
            Y_Lock(access);
            try
            {
                const unsigned      shift     = CeilLog2(blockSize);
                void * const        blockAddr = code->acquire(shift);
                blockSize = Code::_1 << shift;
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
            // sanity check
            assert( 0 != code);
            assert( 0 != blockAddr );
            assert( IsPowerOfTwo(blockSize) );
            const unsigned shift = ExactLog2(blockSize);
            assert( (Code::_1 << shift) == blockSize);

            // locked release
            Y_Lock(access);
            code->release(blockAddr,shift);
            blockAddr = 0;
            blockSize = 0;
        }

        void * Dyadic:: acquireBlock(const unsigned shift)
        {
            // sanity check
            assert( 0 != code );
            assert( shift <= Metrics::MaxPageShift );

            // locked acquire
            Y_Lock(access);
            return code->acquire(shift);
        }

        void Dyadic:: releaseBlock(void *const entry, const unsigned int shift) noexcept
        {
            // sanity check
            assert( 0 != code  );
            assert( 0 != entry );
            assert( shift <= Metrics::MaxPageShift );

            // locked release
            Y_Lock(access);
            code->release(entry,shift);
        }

    }
}
