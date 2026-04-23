//! \file

#ifndef Y_CxxArray_Included
#define Y_CxxArray_Included 1

#include "y/container.hpp"
#include "y/container/contiguous/writable.hpp"
#include "y/memory/troop.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/replicate.hpp"

#include "y/object.hpp"
#include "y/swap.hpp"

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
        inline explicit CxxArray(const CopyOf_ &_, READABLE &arr) :
        code( new Code(_,arr) )
        {
        }

        //! replicate \param _ helper \param i first iterator \param n range size
        template <typename ITERATOR>
        inline explicit CxxArray(const Replicate_ &_, ITERATOR i, const size_t n) :
        code( new Code(_,i,n) )
        {}

        //! replicate full sequence \param _ helper \param seq source
        template <typename SEQUENCE>
        inline explicit CxxArray(const Replicate_ &_, SEQUENCE &seq) :
        code( new Code(_,seq.begin(),seq.size()) )
        {}


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
        // Methods
        //
        //______________________________________________________________________

        //! no-throw exchange \param other another array \return *this
        inline CxxArray & xch( CxxArray &other ) noexcept
        {
            CoerceSwap(code,other.code); return *this;
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
        typedef Memory::Troop<MutableType,Object> CodeMemory;
        class Code : public CodeMemory
        {
        public:
            using CodeMemory::addr;
            using CodeMemory::size;

            inline explicit Code(const size_t n) : CodeMemory(n) {
                while(size<n) this->pushTail();
            }

            inline explicit Code(const size_t n, ConstType &value) : CodeMemory(n) {
                while(size<n) this->pushTail(value);
            }

            template <typename READABLE>
            inline explicit Code(const CopyOf_ &, READABLE &arr) : CodeMemory(arr.size()) {
                this->copy(arr);
            }

            template <typename ITERATOR>
            inline explicit Code(const Replicate_ &, ITERATOR i, const size_t n) : CodeMemory(n)
            {
                this->replicate(i,n);
            }

            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}



#endif // !Y_CxxArray_Included

