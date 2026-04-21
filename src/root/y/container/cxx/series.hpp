
//! \file

#ifndef Y_CxxSeries_Included
#define Y_CxxSeries_Included 1

#include "y/container/contiguous/writable.hpp"
#include "y/container/sequence.hpp"
#include "y/memory/troop/joint.hpp"
#include "y/type/destroy.hpp"
#include "y/type/copy-of.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/copy.h"
#include "y/ability/recyclable.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Series of Objects within fixed capacity
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class CxxSeries :
    public Sequence<T, ContiguousWritable<T> >,
    public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);                                   //!< aliases
        typedef Sequence<T, ContiguousWritable<T> > SequenceType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minCapacity minimal capacity
        inline explicit CxxSeries(const size_t minCapacity) : code( new Code(minCapacity) )
        {
        }

        //! cleanup
        inline virtual ~CxxSeries() noexcept { assert(code); Destroy(code); }

        //! duplicate \param _ helper \param arr readable array
        template <typename READABLE>
        inline explicit CxxSeries(const CopyOf_ &_, const READABLE &arr) :
        code( new Code(_,arr) )
        {
        }

        //______________________________________________________________________
        //
        //
        // Interfacce
        //
        //______________________________________________________________________
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

        //! todo
        virtual void remove(const size_t indx) noexcept
        {
            assert(code); code->remove(indx);
        }

        //! todo
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

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        class Code;
        Y_Disable_Copy_And_Assign(CxxSeries); //!< discarded
        Code * const code;                    //!< inner code

        inline virtual ConstType & getTail() const noexcept {
            assert(code); assert(code->size); return code->cxx[code->size];
        }

        inline virtual ConstType & getHead() const noexcept {
            assert(code); assert(code->size); return code->addr[0];
        }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        typedef Memory::JointTroop<MutableType> CodeMemory;
        class Code : public Object, public CodeMemory
        {
        public:
            inline explicit Code(const size_t n) : Object(), CodeMemory(n) {}
            inline virtual ~Code() noexcept {}
            template <typename READABLE>
            inline explicit Code(const CopyOf_ &_, const READABLE &arr) :
            Object(), CodeMemory(_,arr)
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


    };

}

#endif // !Y_CxxSeries_Included

