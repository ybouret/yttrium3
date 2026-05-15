
//! \file

#ifndef Y_Cameo_Add_FP_Queue_Included
#define Y_Cameo_Add_FP_Queue_Included 1


#include "y/cameo/fp-queue.hpp"
#include "y/container/ordered/prio-q.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/cameo/summator.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        template <typename T>
        class QAdd
        {
        public:
            Y_Args_Declare(T,Type);
            inline QAdd(ParamType value) noexcept :
            data(value),
            rank(MKL::Fabs<MutableType>(data))
            {
            }

            inline QAdd(const QAdd &it) noexcept :
            data(it.data),
            rank(it.rank)
            {

            }

            inline ~QAdd() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const QAdd &self)
            {
                return os << '|' << self.data << '|';
            }

            inline ConstType & operator*() const noexcept { return data; }

            inline friend QAdd operator+(const QAdd &lhs, const QAdd &rhs) noexcept
            {
                return QAdd(lhs.data+rhs.data);
            }

            class Comparator
            {
            public:
                inline  Comparator() noexcept {}
                inline ~Comparator() noexcept {}

                inline int operator()(const QAdd &lhs, const QAdd &rhs) noexcept
                {
                    return (lhs.rank < rhs.rank) ? -1 : ( (rhs.rank<lhs.rank) ? 1 : 0);
                }

            };

        private:
            ConstType data;
            ConstType rank;
            Y_Disable_Assign(QAdd);
        };

        template <
        typename T,
        typename PQ // Priority queue for QAdd<T>
        >
        class FP_QAdd : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);
            typedef QAdd<T> Item;

            inline FP_QAdd() : pq() {}
            inline FP_QAdd(const size_t minCapacity) : pq(minCapacity) {}
            inline FP_QAdd(const FP_QAdd &other) : Summator<T>(), pq(other.pq) {}

            inline virtual ~FP_QAdd() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const FP_QAdd &self)
            {
                return os << self.pq;
            }

            inline virtual void ldz() noexcept { pq.free(); }
            inline void         add(ConstType &data) {
                const Item item(data); pq.push(item);
            }

            inline virtual Type operator()(void)
            {
                switch(pq.size())
                {
                    case 0: return 0;
                    case 1: return *pq.pull();
                    default:
                        break;
                }
                while(pq.size()>1)
                {
                    const Item lhs = pq.pull(); assert(pq.size()>0);
                    const Item rhs = pq.pull();
                    std::cerr << "=> " << lhs << " + " << rhs << std::endl;
                    pq << lhs+rhs;
                }
                assert(1==pq.size());
                return *pq.pull();
            }

        private:
            Y_Disable_Assign(FP_QAdd);
            PQ pq;
        };


        template <typename T>
        class FP_QueueSummator : public FP_QAdd<T,PriorityQ< QAdd<T>, typename QAdd<T>::Comparator > >
        {
        public:
            typedef QAdd<T> Item;
            typedef PriorityQ<Item,typename Item::Comparator> PQ_Type;
            typedef FP_QAdd<T,PQ_Type> SummatorType;

            inline explicit FP_QueueSummator() : SummatorType() {}
            inline explicit FP_QueueSummator(const size_t minCapacity) : SummatorType(minCapacity) {}
            inline virtual ~FP_QueueSummator() noexcept {}


        private:
            Y_Disable_Copy_And_Assign(FP_QueueSummator);
        };


    }

}


#endif // !Y_Cameo_Add_FP_Queue_Included

