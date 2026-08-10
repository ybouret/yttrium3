
#include "y/concurrent/api/local/cache.hpp"
#include "y/type/destroy.hpp"

#include "y/memory/allocator/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/system/error.hpp"

#include <cerrno>
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace
        {
            static const char CallSign[] = "Concurrent::LocalCache";
        }

        class LocalCache:: Code : public Object
        {
        public:
            typedef Memory::Archon MemMgr;

            inline explicit Code() noexcept: entry(0), bytes(0), locked(false) {}


            inline virtual ~Code() noexcept {
                release();
                if(locked) Libc::Error::Critical(EINVAL,"%s stilled locked!",CallSign);
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
                    (void) memset(entry,0,bytes);

            }


            void *   entry;
            size_t   bytes;
            bool     locked;

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
            if(code->locked) Libc::Error::Critical(EINVAL,"%s.ensure() while locked!",CallSign);
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



        void LocalCache:: lock() noexcept
        {
            assert(code);
            if(code->locked) Libc::Error::Critical(EINVAL,"%s already locked!",CallSign);
            code->locked = true;
        }

        void LocalCache:: unlock() noexcept
        {
            assert(code);
            if(!code->locked) Libc::Error::Critical(EINVAL,"%s already unlocked!",CallSign);
            code->locked = false;
        }

    }

}


