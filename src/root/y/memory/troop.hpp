//! \file

#ifndef Y_Memory_Troop_Included
#define Y_Memory_Troop_Included 1

#include "y/memory/allocator.hpp"
#include "y/type/args.hpp"

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
        class Troop :  public TroopGear
        {
        public:
            Y_Args_Expose(T,Type);

            inline explicit Troop(const size_t minCapacity) :
            bytes(0),
            capacity(minCapacity),
            addr( static_cast<MutableType *>( Acquire(Coerce(capacity), Coerce(bytes), sizeof(T))) ),
            cxx(addr-1)
            {
            }

            inline virtual ~Troop() noexcept
            {
                if(addr)
                {
                    Release(addr,Coerce(capacity),Coerce(bytes));
                    Coerce(addr) = 0;
                }
                Coerce(cxx)  = 0;
                assert(0==addr);
                assert(0==capacity);
                assert(0==bytes);
            }


            const size_t        bytes;
            const size_t        capacity; //!< maximum capacity
            MutableType * const addr;  //!< legacy address [0:count-1]
            MutableType * const cxx;   //!< C++ address [1:count]

        private:
            Y_Disable_Copy_And_Assign(Troop);
        };

    }
}

#endif // !Y_Memory_Troop_Included

