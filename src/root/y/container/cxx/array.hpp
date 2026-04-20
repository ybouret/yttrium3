//! \file

#ifndef Y_CxxArray_Included
#define Y_CxxArray_Included 1

#include "y/container.hpp"
#include "y/container/contiguous/rw.hpp"
#include "y/container/writable.hpp"
#include "y/memory/troop.hpp"
#include "y/memory/auto-built.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{

    template <typename T>
    class CxxArray : public ReadWriteContiguous< Writable<T> >
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
        Y_Disable_Assign(CxxArray);
        Code * const code;

        typedef Memory::Troop<MutableType,Object> CodeMemory;
        typedef Memory::AutoBuilt<Type>           CodeMaster;

        class Code : public CodeMemory, public CodeMaster
        {
        public:
            using CodeMemory::addr;

            inline explicit Code(const size_t n) :
            CodeMemory(n),
            CodeMaster(addr,n),
            size(n)
            {
            }

            inline explicit Code(const size_t n, ConstType &value) :
            CodeMemory(n),
            CodeMaster(addr,n,value),
            size(n)
            {
            }



            inline virtual ~Code() noexcept
            {
                Coerce(size) = 0;
            }

            const size_t size;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
    };

}



#endif // !Y_CxxArray_Included

