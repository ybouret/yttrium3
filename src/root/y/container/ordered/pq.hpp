
//! \file

#ifndef Y_Container_PrioQ_Included
#define Y_Container_PrioQ_Included 1


#include "y/config/setup.hpp"
#include "y/type/args.hpp"
#include "y/libc/pq/api.h"
#include "y/libc/block/zeroed.h"
#include "y/libc/block/zero.h"
#include "y/core/display.hpp"
#include "y/type/pulverize.hpp"
#include <cassert>

namespace Yttrium
{

    template <typename T>
    class PrioQ
    {
    public:
        Y_Args_Declare(T,Type);

        //! blockAddr[numBlocks*sizeof(T)]
        inline PrioQ(void * const blockAddr,
                     const size_t numBlocks) noexcept :
        capacity(numBlocks),
        size(0),
        addr( (MutableType *) blockAddr ),
        bytes( capacity * sizeof(T) )
        {
            assert( !(0==addr&&capacity>0) );
            assert( Y_TRUE == Yttrium_Zeroed(addr,bytes) );
        }

        inline virtual ~PrioQ() noexcept
        {
            free();
        }

        inline friend std::ostream & operator<<(std::ostream &os, const PrioQ &pq)
        {
            return Core::Display(os,pq.addr,pq.size);
        }


        template <typename COMPARE> inline
        void push(COMPARE &proc, ParamType data) {
            assert(size<capacity);
            new (addr+size) MutableType(data);
            Yttrium_PQ_Push_Balance(addr,++Coerce(size),sizeof(T), cmp<COMPARE>, (void *) &proc );
        }

        inline ConstType & peek() const noexcept
        {
            assert(size>0);
            return addr[0];
        }

        template <typename COMPARE> inline
        void pop(COMPARE &proc) noexcept
        {
            assert(size>0);
            Pulverize(addr);
            Yttrium_PQ_Pull_Balance(addr,--Coerce(size),sizeof(T), cmp<COMPARE>, (void *) &proc );
        }

        template <typename COMPARE> inline
        Type pull(COMPARE &proc)
        {
            assert(size>0);
            ConstType save = addr[0];
            pop<COMPARE>(proc); return save;
        }


        inline void free() noexcept
        {
            while(size>0)
                Pulverize(&addr[--Coerce(size)]);
            assert( Y_TRUE == Yttrium_Zeroed(addr,bytes) );
        }





        const size_t capacity;
        const size_t size;
    private:
        Y_Disable_Copy_And_Assign(PrioQ);
        MutableType * const addr;
        template <typename COMPARE> static
        inline int cmp(const void * const lhs, const void * const rhs, void * const args)
        {
            assert(args); assert(lhs); assert(rhs);
            COMPARE   &proc = *(COMPARE *)args;
            ConstType &lobj = *static_cast<ConstType*>(lhs);
            ConstType &robj = *static_cast<ConstType*>(rhs);
            return proc(lobj,robj);
        }

    public:
        const size_t bytes;
    };

}

#endif // !Y_Container_PrioQ_Included

