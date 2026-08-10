
//! \file

#ifndef Y_Concurrent_LocalCache_Included
#define Y_Concurrent_LocalCache_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class LocalCache : public CountedObject, public Memory::ReadWriteBuffer
        {
        public:
            class Code;
            explicit LocalCache();
            virtual ~LocalCache() noexcept;

            LocalCache & ensure(const size_t blockSize, const size_t numBlocks);

            template <typename T> inline
            LocalCache & ensure(const size_t numBlocks) {
                return ensure(sizeof(T),numBlocks);
            }


            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(LocalCache);
            Code * const code;
        };
    }

}

#endif // !Y_Concurrent_LocalCache_Included
