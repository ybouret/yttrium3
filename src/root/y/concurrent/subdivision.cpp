#include "y/concurrent/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Subdivision:: ~Subdivision() noexcept
        {
        }

        Subdivision:: Subdivision(const size_t sz,
                                  const size_t rk,
                                  Lockable    &lk) noexcept :
        Context(sz,rk,lk),
        entry(0),
        bytes(0)
        {
        }

        Subdivision:: Subdivision(const Context &ctx)  noexcept :
        Context(ctx),
        entry(0),
        bytes(0)
        {
        }


        

        
        void Subdivision:: borrowFrom(Memory::ReadWriteBuffer &buffer) noexcept
        {
            const size_t length = borrowable(buffer.length());

            if(length<=0)
                clearCache();
            else
            {
                char * const addr = static_cast<char *>(buffer.rw());
                Coerce(entry) = & addr[ rank*length ];
                Coerce(bytes) = length;
            }

        }

        void Subdivision:: clearCache() noexcept
        {
            Coerce(entry) = 0;
            Coerce(bytes) = 0;
        }

    }

}
