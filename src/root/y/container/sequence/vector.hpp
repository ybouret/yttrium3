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
#include "y/ability/recyclable.hpp"
#include "y/ability/releasable.hpp"
#include "y/ability/expandable.hpp"
#include "y/swap.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Vector
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Vector :
    public Sequence<T,ContiguousWritable<T>>,
    public Expandable<Releasable>,
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

        //! setup empty
        inline explicit Vector() : code( new Code(0) ) {}

        //! setup \param n with memory for at least n items
        inline explicit Vector(const WithAtLeast_ &, const size_t n) : code( new Code(n) )
        {
            assert( capacity() >= n );
        }


        //! duplicate \param _ helper \param arr readable array
        template <typename READABLE>
        inline explicit Vector(const CopyOf_ &_, READABLE &arr) :
        code( new Code(_,arr) )
        {
        }

        //! replicate \param _ helper \param i first iterator \param n range size
        template <typename ITERATOR>
        inline explicit Vector(const Replicate_ &_, ITERATOR i, const size_t n) :
        code( new Code(_,i,n) )
        {}

        //! replicate full sequence \param _ helper \param seq source
        template <typename SEQUENCE>
        inline explicit Vector(const Replicate_ &_, SEQUENCE &seq) :
        code( new Code(_,seq.begin(),seq.size()) )
        {}


        //! cleanup
        inline virtual ~Vector() noexcept { assert(code); Destroy(code); }

        //! assign by copy/exchange \param v another vector \return *this
        Vector & operator=(const Vector &v) {
            Vector temp(CopyOf,v); return xch(temp);
        }

        //! assign by copy/exchange \param other compatible readadble \return *this
        template <typename READABLE>
        Vector & operator=( READABLE &other ) {
            Vector temp(CopyOf,other); return xch(temp);
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()     const noexcept { assert(code); return code->size;      }
        inline virtual size_t capacity() const noexcept { assert(code); return code->capacity;  }
        inline virtual void   free()           noexcept { assert(code); return code->free();    }
        inline virtual void   release()        noexcept { assert(code); return code->release(); }

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
                trade(new Code( Container::NextCapacity(code->capacity) ) );
                Yttrium_BCopy(code->addr+Coerce(code->size)++,data,sizeof(T)); Y_BZero(wksp);
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
                Yttrium_BCopy(temp->addr+Coerce(temp->size)++,data,sizeof(T)); Y_BZero(wksp);
                trade(temp);
            }
        }

        inline virtual void reserve(const size_t n)
        {
            assert(code); trade( new Code(code->capacity+n) );
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! no-throw exchange \param other another vector \return *this
        inline Vector & xch(Vector &other) noexcept {
            CoerceSwap(code,other.code); return *this;
        }


    private:
        class Code;
        Y_Disable_Copy(Vector); //!< discarded
        Code * const code;      //!< inner memory

        //! trade code \param temp will be new captured code
        inline void trade(Code * const temp) noexcept
        {
            assert(temp!=code);
            temp->capture(*code);
            delete code;
            Coerce(code) = temp;
        }

        inline virtual ConstType &ask(const size_t indx) const noexcept {
            assert(code);
            assert(indx>=1); assert(indx<=code->size);
            return code->cxx[indx];
        }

        inline virtual ConstType & getTail() const noexcept {
            assert(code); assert(code->size); assert(code->addr); return code->cxx[code->size];
        }

        inline virtual ConstType & getHead() const noexcept {
            assert(code); assert(code->size);  assert(code->addr); return code->addr[0];
        }


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        typedef Memory::JointTroop<MutableType> CodeMemory;
        class Code : public Object, public CodeMemory
        {
        public:
            inline explicit Code(const size_t n) : Object(), CodeMemory(n) {}
            inline virtual ~Code() noexcept {}

            template <typename READABLE>
            inline explicit Code(const CopyOf_  &,
                                 READABLE       &arr) :
            Object(), CodeMemory(arr.size())
            {
                this->copy(arr);
            }

            template <typename ITERATOR>
            inline explicit Code(const Replicate_ &, ITERATOR i, const size_t n) :
            Object(), CodeMemory(n)
            {
                this->replicate(i,n);
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}


#endif // !Y_Vector_Included

