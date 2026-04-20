
//! \file

#ifndef Y_CxxSeries_Included
#define Y_CxxSeries_Included 1

#include "y/container/cxx/container.hpp"
#include "y/container/contiguous/rw.hpp"
#include "y/container/writable.hpp"
#include "y/container/sequence.hpp"
#include "y/ability/random-access.hpp"
#include "y/memory/troop.hpp"
#include "y/type/destroy.hpp"
#include "y/type/destruct.hpp"
#include "y/type/copy-of.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/move.h"
#include "y/libc/block/copy.h"



namespace Yttrium
{

    template <typename T>
    class CxxSeries : public Sequence<T,ReadWriteContiguous< Writable<T> > >
    {
    public:
        Y_Args_Declare(T,Type);
        
        inline explicit CxxSeries(const size_t minCapacity) : code( new Code(minCapacity) )
        {
        }
        

        inline virtual ~CxxSeries() noexcept { assert(code); Destroy(code); }


        inline virtual size_t size()     const noexcept { assert(code); return code->size; }
        inline virtual size_t capacity() const noexcept { assert(code); return code->capacity; }

        virtual void pushTail(ParamType args) noexcept
        {
            assert(code); code->pushTail(args);
        }


        virtual void pushHead(ParamType args) noexcept
        {
            assert(code); code->pushHead(args);
        }



    protected:
        virtual ConstType &ask(const size_t indx) const noexcept
        {
            assert(code);
            assert(indx>=1); assert(indx<=code->size);
            return code->cxx[indx];
        }
    private:
        class Code;
        Y_Disable_Copy_And_Assign(CxxSeries);
        Code * const code;

        typedef CxxContainer               CodeObject;
        typedef Memory::Troop<MutableType> CodeMemory;

        class Code : public CodeObject, public CodeMemory
        {
        public:
            using CodeMemory::addr;
            using CodeMemory::bytes;
            using CodeMemory::capacity;

            inline explicit Code(const size_t minCapacity) :
            CodeObject(0), CodeMemory(minCapacity) {}

            inline virtual ~Code() noexcept { free(); }

            inline void free() noexcept {
                while(size>0) Destruct(&addr[--Coerce(size)]);
                Yttrium_BZero(addr,bytes);
            }

            template <typename ARGS>
            inline void pushTail(const ARGS &args)
            {
                assert(size<capacity);
                new (addr+size) MutableType(args);
                ++Coerce(size);
            }

            template <typename ARGS>
            inline void pushHead(const ARGS &args)
            {
                assert(size<capacity);
                void *              wksp[ Alignment::WordsFor<T>::Count ];
                MutableType * const temp = new (static_cast<MutableType *>(Y_BZero(wksp))) MutableType(args);
                Yttrium_BMove(addr+1,addr,sizeof(T) * Coerce(size)++ );
                Yttrium_BCopy(addr,temp,sizeof(T));
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

    };

}

#endif // !Y_CxxSeries_Included

