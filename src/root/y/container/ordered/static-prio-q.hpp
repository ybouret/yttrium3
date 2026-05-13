
//! \file

#ifndef Y_Container_StaticPQ_Included
#define Y_Container_StaticPQ_Included 1


#include "y/container/ordered.hpp"
#include "y/container/ordered/pq.hpp"
#include "y/type/sign.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{

    template <
    typename T,
    size_t   N,
    typename COMPARATOR = Sign::Comparator<T>
    >
    class StaticPrioQ : public Ordered<T>
    {
    public:
        typedef PrioQ<T> PQ;
        Y_Args_Declare(T,Type);

        inline explicit StaticPrioQ() noexcept :
        pq(0),
        cmp(),
        prio(),
        wksp()
        {
            init();
        }

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

        inline virtual ~StaticPrioQ() noexcept
        {
            quit();
        }

        inline friend std::ostream & operator<<(std::ostream &os, const StaticPrioQ &self)
        {
            return os << *self.pq;
        }

        inline virtual size_t size()     const noexcept { return pq->size;     }
        inline virtual size_t capacity() const noexcept { return pq->capacity; }


        inline virtual void        push(ParamType data)  { pq->push(cmp,data); }
        inline virtual ConstType & peek() const noexcept { return pq->peek();  }
        inline virtual void        pop()        noexcept { pq->pop(cmp); }

    private:
        Y_Disable_Assign(StaticPrioQ);
        PQ * const pq;
        COMPARATOR cmp;
        void *     prio[ Alignment::WordsFor<PQ>::Count ];
        void *     wksp[ Alignment::WordsGEQ<N*sizeof(T)>::Count ];

        inline void init() noexcept
        {
            Coerce(pq) = new (Y_BZero(prio)) PQ(Y_BZero(wksp),N);
        }

        inline void quit() noexcept
        {
            Pulverize(pq); Coerce(pq) = 0;
        }
    };

}

#endif // !Y_Container_StaticPQ_Included

