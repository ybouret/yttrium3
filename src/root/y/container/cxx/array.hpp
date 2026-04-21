//! \file

#ifndef Y_CxxArray_Included
#define Y_CxxArray_Included 1

#include "y/container.hpp"
#include "y/container/contiguous/writable.hpp"
#include "y/memory/troop.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Fixed capacity, pre-allocated array of objects
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class CxxArray : public ContiguousWritable<T>
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

        //! setup with initial size, default constructor \param n required size
        inline explicit CxxArray(const size_t n) : code( new Code(n) )
        {
        }

        //! setup
        /**
         \param n     required size
         \param value filling value
         */
        inline explicit CxxArray(const size_t n, const ParamType value) :
        code( new Code(n,value) )
        {
        }

        //! setup
        /**
         \param n     required size
         \param value (any) filling value
         */
        template <typename U>
        inline explicit CxxArray(const size_t n, const CopyOf_ &, U &value) :
        code( new Code(n,value) )
        {
        }

        //! duplicate \param _ helper \param arr readable array
        template <typename READABLE>
        inline explicit CxxArray(const CopyOf_ &_, const READABLE &arr) :
        code( new Code(_,arr) )
        {
        }

        //! cleanup
        inline virtual ~CxxArray() noexcept
        {
            assert(code); Destroy(code);
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()     const noexcept { assert(code); return code->size; }
        inline virtual size_t capacity() const noexcept { assert(code); return code->size; }


    protected:
        virtual ConstType &ask(const size_t indx) const noexcept
        {
            assert(code);
            assert(indx>=1); assert(indx<=code->size);
            return code->cxx[indx];
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        class Code;
        Y_Disable_Copy_And_Assign(CxxArray); //!< dicarded
        Code * const code;                   //!< inner code


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        typedef Memory::Troop<MutableType> CodeMemory;
        class Code : public Object, public CodeMemory
        {
        public:
            using CodeMemory::addr;
            using CodeMemory::size;

            inline explicit Code(const size_t n) :
            CodeMemory(n)
            {
                while(size<n) this->pushTail();
            }

            inline explicit Code(const size_t n, ConstType &value) :
            CodeMemory(n)
            {
                while(size<n) this->pushTail(value);
            }

            template <typename READABLE>
            inline explicit Code(const CopyOf_ &, const READABLE &arr) :
            CodeMemory(arr.size())
            {
                this->copy(arr);
            }

            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}



#endif // !Y_CxxArray_Included

