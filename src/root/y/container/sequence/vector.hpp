//! \file

#ifndef Y_Vector_Included
#define Y_Vector_Included 1

#include "y/container/sequence.hpp"
#include "y/memory/troop/joint.hpp"
#include "y/container/contiguous/writable.hpp"
#include "y/object.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/replicate.hpp"
#include "y/type/destroy.hpp"
#include "y/type/with-at-least.hpp"

namespace Yttrium
{

    template <typename T>
    class Vector : public Sequence<T,ContiguousWritable<T> >
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

        inline explicit Vector() : code( new Code(0) ) {}

        inline explicit Vector(const WithAtLeast_ &, const size_t n) : code( new Code(n) )
        {
            assert( capacity() >= n );
        }


        inline virtual ~Vector() noexcept
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
        inline virtual size_t capacity() const noexcept { assert(code); return code->capacity; }

        inline virtual void   popTail()  noexcept { assert(code); code->popTail(); }
        inline virtual void   popHead()  noexcept { assert(code); code->popHead(); }

        inline virtual void pushTail(ParamType args)
        {
            assert(code);
            if(code->size<code->capacity)
                code->pushTail(args);
            else
            {
                void *              wksp[ Alignment::WordsFor<T>::Count ];
                MutableType * const data = new ( Y_BZero(wksp) ) MutableType(args);
                {
                    Code * const temp = new Code( Container::NextCapacity(code->capacity) );
                    temp->capture( *code ); assert(0==code->size);
                    delete code; Coerce(code) = temp;
                }
                Yttrium_BCopy(code->addr+Coerce(code->size)++,data,sizeof(T));
                Y_BZero(wksp);
            }

        }

        inline virtual void pushHead(ParamType args)
        {
            assert(code);
            if(code->size<code->capacity)
                code->pushHead(args);
            else
            {
                void *              wksp[ Alignment::WordsFor<T>::Count ];
                MutableType * const data = new ( Y_BZero(wksp) ) MutableType(args);
                Code * const        temp = new Code( Container::NextCapacity(code->capacity) );
                Yttrium_BCopy(temp->addr+Coerce(temp->size)++,data,sizeof(T));
                Y_BZero(wksp);
                temp->capture(*code); assert(0==code->size);
                delete code; Coerce(code) = temp;
            }
        }


    private:
        class Code;
        Y_Disable_Copy(Vector);
        Code * const code;

        inline virtual ConstType &ask(const size_t indx) const noexcept {
            assert(code);
            assert(indx>=1); assert(indx<=code->size);
            return code->cxx[indx];
        }

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

            template <typename ITERATOR>
            inline explicit Code(const Replicate_ &_, ITERATOR i, const size_t n) :
            Object(), CodeMemory(_,i,n)
            {
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}


#endif // !Y_Vector_Included

