#include "y/memory/allocator/dyadic.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/small/blocks.hpp"
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

            Code(Concurrent::Nucleus &nucleus) :
            dyadicArena(),
            smallBlocks(nucleus.blocks)
            {
                std::cerr << "+" << CallSign << "::Code" << std::endl;
                Y_BZero(dyadicArena);
            }

            ~Code() noexcept {}

            Memory::Small::Arena *  dyadicArena[NumSmall];
            Memory::Small::Blocks & smallBlocks;
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
        }

        void * Dyadic:: acquire(size_t &blockSize)
        {
            if(blockSize>Base2<size_t>::MaxBytes)
                throw Specific::Exception(CallSign,"blockSize overflow");


        }

        void Dyadic:: release(void * & blockAddr, size_t & blockSize) noexcept
        {
            assert( 0 != blockAddr );
            assert( IsPowerOfTwo(blockSize) );
        }
    }
}
