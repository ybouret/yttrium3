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

        //______________________________________________________________________
        //
        //
        //
        //! Managing data for Troop
        //
        //
        //______________________________________________________________________
        class TroopGear
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit TroopGear() noexcept; //!< setup
            virtual ~TroopGear() noexcept; //!< cleanup

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            //__________________________________________________________________
            //
            //
            // Helpers
            //
            //__________________________________________________________________
            static void * Acquire(size_t &count, size_t &bytes, const size_t bytesPerItem);
            static void   Release(void * const addr, size_t &count, size_t &bytes) noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        private:
            Y_Disable_Copy_And_Assign(TroopGear); //!< discarded
        };

        //______________________________________________________________________
        //
        //
        //
        //! Basic linear memory management
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Troop : public TroopGear
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param minCapacity minimal capacity
            inline explicit Troop(const size_t minCapacity) :
            size(0),
            capacity(minCapacity),
            bytes(0),
            addr( static_cast<MutableType *>( Acquire(Coerce(capacity), Coerce(bytes), sizeof(T))) ),
            cxx(addr-1)
            {
            }

            //! cleanup
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

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! push new default element at tail
            inline void pushTail() {
                assert(size<capacity);
                MutableType * const target = addr+size;
                try        { new (target) MutableType(); ++Coerce(size); }
                catch(...) { Yttrium_BZero(target,sizeof(T)); throw;     }

            }

            //! push any compatile element at tail \param args any compatible argument
            template <typename ARGS> inline
            void pushTail(ARGS &args) {
                assert(size<capacity);
                MutableType * const target = addr+size;
                try        { new (target) MutableType(args); ++Coerce(size); }
                catch(...) { Yttrium_BZero(target,sizeof(T)); throw;         }
            }

            //! remove tail element
            inline void popTail() noexcept {
                assert(size>0);
                (void) Yttrium_BZero( Destructed(& addr[--Coerce(size)]), sizeof(T) );
            }

            //! remove all elements (memory is kept)
            inline void free() noexcept { while(size>0) popTail(); }


            //! sequential copy \param arr readable source
            template <typename READABLE> inline
            void copy(const READABLE &arr) {
                assert(0==size); assert(capacity>=arr.size());
                const size_t n = arr.size();
                try        { for(size_t i=1;i<=n;++i) pushTail(arr[i]); }
                catch(...) { free(); throw; }
            }

            //! replicate range \param i first iterator \param n range size
            template <typename ITERATOR> inline
            void replicate(ITERATOR i, size_t n)
            {
                assert(0==size); assert(capacity>=n);
                try        { while( n-- > 0 ) pushTail( *(i++) ); }
                catch(...) { free(); throw; }
            }

            //! capture memory in empty space \param troop source
            inline void capture(Troop &troop) noexcept {
                assert(capacity>=troop.size); assert(0==size); assert(this != &troop );
                const size_t blockSize = (Coerce(size)=troop.size) * sizeof(T);
                Yttrium_BCopy(addr,troop.addr,blockSize);
                Yttrium_BZero(troop.addr,blockSize);
                Coerce(troop.size) = 0;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t        size;     //!< current size
            const size_t        capacity; //!< maximum capacity
            const size_t        bytes;    //!< allocated bytes
            MutableType * const addr;     //!< legacy address [0:count-1]
            MutableType * const cxx;      //!< C++ address [1:count]

        private:
            Y_Disable_Copy_And_Assign(Troop); //!< discarded
        };

    }
}

#endif // !Y_Memory_Troop_Included

