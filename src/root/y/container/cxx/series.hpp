
//! \file

#ifndef Y_CxxSeries_Included
#define Y_CxxSeries_Included 1

#include "y/container/contiguous/writable.hpp"
#include "y/container/sequence.hpp"
#include "y/ability/random-access.hpp"
#include "y/memory/troop/joint.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/copy.h"
#include "y/ability/recyclable.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    template <typename T>
    class CxxSeries :
    public Sequence<T, ContiguousWritable<T> >,
    public Recyclable,
    public RandomAccess<T>
    {
    public:
        Y_Args_Declare(T,Type);
        typedef Sequence<T, ContiguousWritable<T> > SequenceType;

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

        virtual void popTail() noexcept
        {
            assert(code); code->popTail();
        }

        virtual void popHead() noexcept
        {
            assert(code); code->popHead();
        }

        virtual void free() noexcept
        {
            assert(code); code->free();
        }

        virtual void remove(const size_t indx) noexcept
        {
            assert(code); code->remove(indx);
        }

        
        virtual void demote(const size_t indx) noexcept
        {
            assert(code); code->demote(indx);
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

        typedef Memory::JointTroop<MutableType> CodeMemory;

        class Code : public Object, public CodeMemory
        {
        public:
            inline explicit Code(const size_t n) : Object(), CodeMemory(n) {}
            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Code);
        };



    };

}

#endif // !Y_CxxSeries_Included

