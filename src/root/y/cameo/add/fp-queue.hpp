
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
            rank(MKL::Fabs(data))
            {
            }

            inline QAdd(const QAdd &it) noexcept :
            data(it.data),
            rank(it.rank)
            {

            }

            inline ~QAdd() noexcept {}


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

            inline virtual void ldz() noexcept { pq.free(); }




        private:
            Y_Disable_Assign(FP_QAdd);
            PQ pq;
        };


    }

}


#endif // !Y_Cameo_Add_FP_Queue_Included

