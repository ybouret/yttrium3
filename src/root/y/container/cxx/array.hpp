//! \file

#ifndef Y_CxxArray_Included
#define Y_CxxArray_Included 1

#include "y/container/cxx/container.hpp"
#include "y/container.hpp"
#include "y/container/contiguous/writable.hpp"
#include "y/memory/troop.hpp"
#include "y/memory/auto-built.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{



    template <typename T>
    class CxxArray : public ContiguousWritable<T>
    {
    public:
        Y_Args_Declare(T,Type);

        inline explicit CxxArray(const size_t n) : code( new Code(n) )
        {
        }

        inline explicit CxxArray(const size_t n, const ParamType value) :
        code( new Code(n,value) )
        {
        }

        template <typename U>
        inline explicit CxxArray(const size_t n, const CopyOf_ &, U &value) :
        code( new Code(n,value) )
        {
        }

        template <typename ARR>
        inline explicit CxxArray(const CopyOf_ &_, const ARR &arr) :
        code( new Code(_,arr) )
        {
        }


        inline virtual ~CxxArray() noexcept
        {
            assert(code); Destroy(code);
        }

        inline virtual size_t size()     const noexcept { assert(code); return code->size; }
        inline virtual size_t capacity() const noexcept { assert(code); return code->capacity; }


    protected:
        virtual ConstType &ask(const size_t indx) const noexcept
        {
            assert(code);
            assert(indx>=1); assert(indx<=code->size);
            return code->cxx[indx];
        }
    private:
        class Code;
        Y_Disable_Copy_And_Assign(CxxArray);
        Code * const code;


        typedef CxxContainer              CodeObject;
        typedef Memory::Troop<MutableType> CodeMemory;
        typedef Memory::AutoBuilt<Type>    CodeMaster;

        class Code : public CodeObject, public CodeMemory, public CodeMaster
        {
        public:
            using CodeMemory::addr;

            inline explicit Code(const size_t n) :
            CodeObject(n),
            CodeMemory(size),
            CodeMaster(addr,size)
            {
            }

            inline explicit Code(const size_t n, ConstType &value) :
            CodeObject(n),
            CodeMemory(size),
            CodeMaster(addr,size,value)
            {
            }

            template <typename ARR>
            inline explicit Code(const CopyOf_ &, const ARR &arr) :
            CodeObject( arr.size() ),
            CodeMemory( size ),
            CodeMaster(Procedural,addr,size,arr)
            {
            }

            inline virtual ~Code() noexcept             { Coerce(size) = 0; }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
    };

}



#endif // !Y_CxxArray_Included

