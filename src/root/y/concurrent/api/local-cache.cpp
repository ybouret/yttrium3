
#include "y/concurrent/api/local-cache.hpp"
#include "y/type/destroy.hpp"

#include "y/memory/allocator/archon.hpp"
#include "y/calculus/alignment.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {


        class LocalCache:: Code : public Object
        {
        public:
            typedef Memory::Archon MemMgr;

            inline explicit Code() : entry(0), bytes(0)
            {
            }


            inline virtual ~Code() noexcept
            {
                release();
            }

            inline void match(const size_t required)
            {
                if(required>bytes)
                {
                    static MemMgr & mgr = MemMgr:: Instance();
                    release();
                    entry = mgr.acquire(bytes=required);
                }
                else
                {
                    (void) memset(entry,0,bytes);
                }
            }


            void *   entry;
            size_t   bytes;

        private:
            Y_Disable_Copy_And_Assign(Code);
            
            inline void release() noexcept
            {
                if(entry)
                {
                    static MemMgr & mgr = MemMgr::Location();
                    assert(bytes>0);
                    mgr.release(entry,bytes);
                }
                else
                {
                    assert(0==bytes);
                }
            }
        };


        LocalCache:: ~LocalCache() noexcept
        {
            Destroy(code);
        }

        LocalCache:: LocalCache() : code( new Code() )
        {

        }

        LocalCache & LocalCache:: ensure(const size_t blockSize, const size_t numBlocks)
        {
            assert(blockSize>0);
            assert(numBlocks>0);
            assert(code);
            const size_t bs       = Alignment::SystemMemory::Ceil(blockSize);
            const size_t required = bs * numBlocks;
            code->match(required);
            return *this;
        }

        size_t LocalCache:: length() const noexcept
        {
            assert(code);
            return code->bytes;
        }

        const void * LocalCache:: ro() const noexcept
        {
            assert(code);
            return code->entry;
        }

        size_t LocalCache:: maxBlockSizeFor(const size_t numBlocks) const noexcept
        {
            assert(code);
            assert(numBlocks>0);
            size_t res = code->bytes/numBlocks;
            while(res>0 && 0 != (res%sizeof(void*))) --res;
            return res;
        }



    }

}


