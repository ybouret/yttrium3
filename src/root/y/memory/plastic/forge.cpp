
#include "y/memory/plastic/forge.hpp"
#include "y/memory/book.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {

            Forge:: Forge(Book     & userBook,
                          Lockable & userLock) noexcept :
            book(   userBook ),
            access( userLock )
            {
            }

            Forge:: ~Forge() noexcept
            {

            }

            Bricks * Forge:: newBricks(const unsigned shift)
            {
                assert(shift>= MinPageShift);
                assert(shift<= MaxPageShift);

                Pages &           alloc = book[shift];
                void *    const   block = alloc.get();
                char * const      dataAddr  = static_cast<char *>(block) + DataOffset;
                const size_t      dataSize  = alloc.pageBytes - DataOffset;
                
                return new(block) Bricks(dataAddr,dataSize,shift);
            }

        }

    }

}
