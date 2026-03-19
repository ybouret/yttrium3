
#include "y/memory/plastic/forge.hpp"
#include "y/memory/book.hpp"
#include "y/core/max.hpp"

#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {

            Forge:: Bucket:: Bucket() noexcept : Bucket_(), cache(0)
            {
            }

            Forge:: Bucket:: ~Bucket() noexcept
            {
            }

        }

    }

}

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {
            Forge:: Forge(Book     & userBook,
                          Lockable & userLock) noexcept :
            buckets(0),
            book(   userBook ),
            access( userLock ),
            wksp()
            {
                Coerce(buckets) = static_cast<Bucket *>( Y_BZero(wksp) )-MinPageShift;
                for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
                {
                    new (buckets+shift) Bucket();
                }
            }


            Forge:: ~Forge() noexcept
            {
                for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
                    Destruct(buckets+shift);
                Y_BZero(wksp);
                Coerce(buckets) = 0;
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

                Pages &           alloc     = book[shift]; assert(shift==alloc.pageShift);
                void *    const   block     = alloc.get();
                char * const      dataAddr  = static_cast<char *>(block) + DataOffset;
                const size_t      dataSize  = alloc.pageBytes - DataOffset;

                return buckets[shift].insertByIncreasingAddress( new (block) Bricks(dataAddr,dataSize,shift) );
            }

            



        }

    }

}
