
#include "y/memory/plastic/forge.hpp"
#include "y/memory/book.hpp"
#include "y/core/max.hpp"

#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {

            Forge:: Forge(Book     & userBook,
                          Lockable & userLock) noexcept :
            last(0),
            list(),
            book(   userBook ),
            access( userLock )
            {
            }

            Forge:: ~Forge() noexcept
            {

            }


            unsigned Forge:: ShiftFor(const size_t blockSize)
            {
                const size_t lower     = DataOffset + 2*sizeof(Brick) + blockSize;
                const size_t predicted = Max(lower,Metrics::DefaultBytes);
                if(predicted>MaxPageBytes)
                    throw Specific::Exception("Forge::ShiftFor", "bytes overflow for blockSize=%s", Decimal(blockSize).c_str());
                return CeilLog2(predicted);
            }

            Bricks * Forge:: newBricks(const unsigned shift)
            {
                assert(shift>= MinPageShift);
                assert(shift<= MaxPageShift);

                Pages &           alloc     = book[shift];
                void *    const   block     = alloc.get();
                char * const      dataAddr  = static_cast<char *>(block) + DataOffset;
                const size_t      dataSize  = alloc.pageBytes - DataOffset;

                return new(block) Bricks(dataAddr,dataSize,shift);
            }

            void * Forge:: acquire(size_t &blockSize)
            {
                if(last)
                {
                    void * const p = last->acquire(blockSize);
                    if(p) return p;
                }
                


            }



        }

    }

}
