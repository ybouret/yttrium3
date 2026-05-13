
//! \file

#ifndef Y_Container_PrioQ_Included
#define Y_Container_PrioQ_Included 1


#include "y/config/setup.hpp"
#include "y/type/args.hpp"
#include "y/libc/pq/api.h"
#include "y/libc/block/zeroed.h"
#include "y/libc/block/zero.h"
#include "y/libc/block/copy.h"
#include "y/core/display.hpp"
#include "y/type/pulverize.hpp"
#include <cassert>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Basic priority queues operations in C++
    /**
     \warning comparisons must NOT throw
     */
    //
    //__________________________________________________________________________
    template <typename T>
    class PrioQ
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        /**
         \param blockAddr with at least numBlocks*sizeof(T) bytes
         \param numBlocks initial capacity
         */
        inline explicit PrioQ(void * const blockAddr,
                              const size_t numBlocks) noexcept :
        capacity(numBlocks),
        size(0),
        addr( (MutableType *) blockAddr )
        {
            assert( !(0==addr&&capacity>0) );
            assert( Y_TRUE == Yttrium_Zeroed(addr,capacity*sizeof(T)) );
        }

        //! cleanup
        inline virtual ~PrioQ() noexcept { free(); }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const PrioQ &pq)
        {
            return Core::Display(os,pq.addr,pq.size);
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! push new value and balance
        /**
         \param proc comparison
         \param data passed to constructor
         */
        template <typename COMPARE> inline
        void push(COMPARE &proc, ParamType data) {
            assert(size<capacity);
            new (addr+size) MutableType(data);
            Yttrium_PQ_Push_Balance(addr,++Coerce(size),sizeof(T), cmp<COMPARE>, (void *) &proc );
        }


        //! \return top value
        inline ConstType & peek() const noexcept {
            assert(size>0);
            return addr[0];
        }

        //! remove to value \param proc comparison
        template <typename COMPARE> inline
        void pop(COMPARE &proc) noexcept
        {
            assert(size>0);
            Pulverize(addr);
            Yttrium_PQ_Pull_Balance(addr,--Coerce(size),sizeof(T), cmp<COMPARE>, (void *) &proc );
        }

        //! remove to value \param proc comparison \return saved top value
        template <typename COMPARE> inline
        Type pull(COMPARE &proc)
        {
            assert(size>0);
            ConstType saved = addr[0];
            pop<COMPARE>(proc); return saved;
        }

        //! free all items
        inline void free() noexcept
        {
            while(size>0)
                Pulverize(&addr[--Coerce(size)]);
            assert( Y_TRUE == Yttrium_Zeroed(addr,capacity*sizeof(T)) );
        }

        //! steal content (no throw) \param pq source
        inline void steal(PrioQ &pq) noexcept
        {
            assert(0==size);
            assert(pq.size<=capacity);
            assert(this != &pq);
            {
                const size_t bs = pq.size * sizeof(T);
                Yttrium_BCopy(addr,pq.addr,bs);
                Yttrium_BZero(pq.addr,bs);
            }
            Coerce(size)    = pq.size;
            Coerce(pq.size) = 0;
        }

        //! duplicate \param pq source
        inline void duplicate(const PrioQ &pq)
        {
            assert(this != &pq);
            assert(0==size);
            try {
                while(size<pq.size)
                {
                    new (addr+size) MutableType( pq.addr[size] );
                    ++Coerce(size);
                }
            }
            catch(...) { free(); throw; }
        }
        
        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

        const size_t        capacity; //!< initial capacity
        const size_t        size;     //!< variable size
    private:
        MutableType * const addr;     //!< top item location

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    private:
        Y_Disable_Copy_And_Assign(PrioQ);
        template <typename COMPARE> static
        inline int cmp(const void * const lhs, const void * const rhs, void * const args)
        {
            assert(args); assert(lhs); assert(rhs);
            COMPARE   &proc = *(COMPARE *)args;
            ConstType &lobj = *static_cast<ConstType*>(lhs);
            ConstType &robj = *static_cast<ConstType*>(rhs);
            return proc(lobj,robj);
        }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

    };

}

#endif // !Y_Container_PrioQ_Included

