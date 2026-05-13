
//! \file

#ifndef Y_Container_StaticPQ_Included
#define Y_Container_StaticPQ_Included 1


#include "y/container/ordered.hpp"
#include "y/container/ordered/pq.hpp"
#include "y/type/sign.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Static Priority Queue
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    size_t   N,
    typename COMPARATOR = Sign::Comparator<T>
    >
    class StaticPrioQ : public Ordered<T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef PrioQ<T>    PQ; //!< alias
        Y_Args_Declare(T,Type); //!< aliase
        static const size_t Capacity = N; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit StaticPrioQ() noexcept :
        pq(0),
        cmp(),
        prio(),
        wksp()
        {
            init();
        }

        //! duplicate \param other another queue
        inline StaticPrioQ(const StaticPrioQ &other) :
        pq(0),
        cmp(),
        prio(),
        wksp()
        {
            init();
            try { pq->duplicate( *other.pq); }
            catch(...) { quit(); throw; }
        }

        //! cleanup
        inline virtual ~StaticPrioQ() noexcept
        {
            quit();
        }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const StaticPrioQ &self)
        {
            return os << *self.pq;
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t      size()     const noexcept { return pq->size;     }
        inline virtual size_t      capacity() const noexcept { return pq->capacity; }
        inline virtual void        push(ParamType data)      { pq->push(cmp,data); }
        inline virtual ConstType & peek()     const noexcept { return pq->peek();  }
        inline virtual void        pop()            noexcept { pq->pop(cmp); }
        inline virtual void        free()           noexcept { pq->free(); }
        
    private:
        Y_Disable_Assign(StaticPrioQ); //!< discarded

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        PQ * const pq;   //!< implementation
        COMPARATOR cmp;  //!< comparator class

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        void *     prio[ Alignment::WordsFor<PQ>::Count ];
        void *     wksp[ Alignment::WordsGEQ<N*sizeof(T)>::Count ];

        inline void init() noexcept { Coerce(pq) = new (Y_BZero(prio)) PQ(Y_BZero(wksp),N); }
        inline void quit() noexcept { Pulverize(pq); Coerce(pq) = 0; }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}

#endif // !Y_Container_StaticPQ_Included

