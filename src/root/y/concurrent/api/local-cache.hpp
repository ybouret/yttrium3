
//! \file

#ifndef Y_Concurrent_LocalCache_Included
#define Y_Concurrent_LocalCache_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Memory to dispatch to SIMD
        //
        //
        //______________________________________________________________________
        class LocalCache : public CountedObject, public Memory::ReadWriteBuffer
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit LocalCache();           //!< setup emtpy
            virtual ~LocalCache() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methids
            //
            //__________________________________________________________________

            LocalCache & ensure(const size_t blockSize, const size_t numBlocks);

            template <typename T> inline
            LocalCache & ensure(const size_t numBlocks) {
                return ensure(sizeof(T),numBlocks);
            }

            size_t maxBlockSizeFor(const size_t numBlocks) const noexcept;



        private:
            Y_Disable_Copy_And_Assign(LocalCache);
            Code * const code;
        };
    }

}

#endif // !Y_Concurrent_LocalCache_Included
