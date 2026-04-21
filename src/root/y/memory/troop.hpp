//! \file

#ifndef Y_Memory_Troop_Included
#define Y_Memory_Troop_Included 1

#include "y/memory/allocator.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/copy.h"

namespace Yttrium
{
    namespace Memory
    {

        class TroopGear
        {
        public:
            explicit TroopGear() noexcept;
            virtual ~TroopGear() noexcept;

            static void * Acquire(size_t &count, size_t &bytes, const size_t bytesPerItem);
            static void   Release(void * const addr, size_t &count, size_t &bytes) noexcept;

        private:
            Y_Disable_Copy_And_Assign(TroopGear);
        };

        template <typename T>
        class Troop : public TroopGear
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit Troop(const size_t minCapacity) :
            size(0),
            capacity(minCapacity),
            bytes(0),
            addr( static_cast<MutableType *>( Acquire(Coerce(capacity), Coerce(bytes), sizeof(T))) ),
            cxx(addr-1)
            {
            }

            inline virtual ~Troop() noexcept
            {
                if(addr) {
                    free();
                    Release(addr,Coerce(capacity),Coerce(bytes));
                    Coerce(addr) = 0;
                }
                Coerce(cxx)  = 0;
                assert(0==addr);
                assert(0==capacity);
                assert(0==bytes);
            }

            inline void pushTail() {
                assert(size<capacity);
                MutableType * const target = addr+size;
                try        { new (target) MutableType(); ++Coerce(size); }
                catch(...) { Yttrium_BZero(target,sizeof(T)); throw;     }

            }

            template <typename ARGS> inline
            void pushTail(ARGS &args) {
                assert(size<capacity);
                MutableType * const target = addr+size;
                try        { new (target) MutableType(args); ++Coerce(size); }
                catch(...) { Yttrium_BZero(target,sizeof(T)); throw;         }
            }

            inline void popTail() noexcept {
                assert(size>0);
                (void) Yttrium_BZero( Destructed(& addr[--Coerce(size)]), sizeof(T) );
            }

            inline void free() noexcept { while(size>0) popTail(); }

            
            template <typename READABLE> inline
            void copy(const READABLE &arr) {
                assert(0==size); assert(capacity>=arr.size());
                const size_t n = arr.size();
                try { for(size_t i=1;i<=n;++i) pushTail(arr[i]); } catch(...) { free(); throw; }
            }

            inline void capture(Troop &troop) noexcept {
                assert(capacity>=troop.size); assert(0==size);
                const size_t blockSize = (Coerce(size)=troop.size) * sizeof(T);
                Yttrium_BCopy(addr,troop.addr,blockSize);
                Yttrium_BZero(troop.addr,blockSize);
                Coerce(troop.size) = 0;
            }

            const size_t        size;     //!< current size
            const size_t        capacity; //!< maximum capacity
            const size_t        bytes;    //!< allocated bytes
            MutableType * const addr;     //!< legacy address [0:count-1]
            MutableType * const cxx;      //!< C++ address [1:count]

        private:
            Y_Disable_Copy_And_Assign(Troop);
        };

    }
}

#endif // !Y_Memory_Troop_Included

