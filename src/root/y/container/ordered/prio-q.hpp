//! \file

#ifndef Y_Container_PriorityQ_Included
#define Y_Container_PriorityQ_Included 1


#include "y/container/ordered.hpp"
#include "y/container/ordered/pq.hpp"
#include "y/type/sign.hpp"
#include "y/object.hpp"
#include "y/ability/expandable.hpp"

namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! base class for priority queue code
        //
        //______________________________________________________________________
        class PQCode : public Object
        {
        public:

            //! setup \param numBlocks minimal capacity \param blockSize bytes per block
            explicit PQCode(const size_t numBlocks, const size_t blockSize);

            //! cleanup
            virtual ~PQCode() noexcept;

        protected:
            const size_t bytes; //!< allocated bytes
            void * const entry; //!< allocated memory
        private:
            Y_Disable_Copy_And_Assign(PQCode); //!< discarded
        };
    }

    //__________________________________________________________________________
    //
    //
    //
    //! Dynamic priority queue
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    typename COMPARATOR = Sign::Comparator<T>
    >
    class PriorityQ : public Expandable< Ordered<T> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef PrioQ<T>    PQ; //!< alias
        Y_Args_Declare(T,Type); //!< aliases
        class Code;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minCapacity minimal capacity
        inline explicit PriorityQ(const size_t minCapacity) :
        code( new Code(minCapacity) ), compare()
        {}

        //! default setup
        inline explicit PriorityQ() :
        code( new Code(0) ), compare()
        {}

        //! duplicate \param other another queue
        inline PriorityQ(const PriorityQ &other) :
        Expandable< Ordered<T> >(),
        code( new Code( *other.code) ), compare()
        {
        }

        //! cleanup
        inline virtual ~PriorityQ() noexcept { Destroy(code); }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const PriorityQ &self)
        {
            return os << *self.code;
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        inline virtual size_t      size()      const noexcept { assert(code); return code->size; }
        inline virtual size_t      capacity()  const noexcept { assert(code); return code->capacity; }
        inline virtual void        free()            noexcept { assert(code); code->free(); }
        inline virtual ConstType & peek()      const noexcept { assert(code); assert(code->size); return code->peek(); }
        inline virtual void        pop()             noexcept { assert(code); assert(code->size); code->pop(compare);  }
        inline virtual void        push(ParamType data)
        {
            if(code->size<code->capacity)
            {
                code->push(compare,data);
            }
            else
            {
                Code * const newCode = new Code( Container::NextCapacity(code->capacity) );
                newCode->steal(*code);
                try {
                    newCode->push(compare,data);
                    delete code;
                    Coerce(code) = newCode;
                }
                catch(...)
                {
                    code->steal(*newCode); delete newCode; throw;
                }
            }
        }


        inline virtual void reserve(const size_t n)
        {
            if(n>0)
            {
                Code * const newCode = new Code( n+code->capacity );
                newCode->steal(*code);
                delete code;
                Coerce(code) = newCode;
            }
        }

    private:
        Y_Disable_Assign(PriorityQ); //!< discarded

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        Code * const code;    //!< inner code
        COMPARATOR   compare; //!< comparator

    public:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        class Code : public Core::PQCode, public PQ
        {
        public:
            inline explicit Code(const size_t minCapacity) :
            Core::PQCode(minCapacity,sizeof(T)),
            PQ(entry,bytes/sizeof(T))
            {
            }

            inline virtual ~Code() noexcept
            {}

            inline explicit Code(const Code &other) :
            Core::PQCode(other.size,sizeof(T)),
            PQ(entry,bytes/sizeof(T))
            {
                this->duplicate(other);
            }

        private:
            Y_Disable_Assign(Code);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


    };


}

#endif // !Y_Container_PriorityQ_Included

