#include "y/container/ordered/prio-q.hpp"
#include "y/object/factory.hpp"

namespace Yttrium
{
    namespace Core
    {
        PQCode:: ~PQCode() noexcept
        {
            static Memory::Allocator &mgr = Object::Factory::Location();
            mgr.release(Coerce(entry),Coerce(bytes));
        }

        static inline void *pqAcquire(size_t &bytes)
        {
            static Memory::Allocator &mgr = Object::Factory::Instance();
            return mgr.acquire(bytes);
        }

        PQCode:: PQCode(const size_t numBlocks, const size_t blockSize) :
        bytes( blockSize * numBlocks ),
        entry( pqAcquire(bytes) )
        {
            assert(blockSize>0);
        }


    }
}
