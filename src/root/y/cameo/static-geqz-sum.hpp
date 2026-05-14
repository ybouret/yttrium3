//! \file

#ifndef Y_Cameo_StaticGEQZSum_Included
#define Y_Cameo_StaticGEQZSum_Included 1

#include "y/cameo/summator.hpp"
#include "y/container/ordered/static-prio-q.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        template <typename T, size_t N>
        class StaticGEQZSum : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);

            inline explicit StaticGEQZSum() noexcept : Q()  {}
            inline virtual ~StaticGEQZSum() noexcept {}

            inline virtual void ldz() noexcept { Q.free(); }
            inline virtual void add(ConstType &data) {
                assert( Sign::GEQZ(data) );
                Q.push(data);
            }
            
            inline virtual Type operator()(void)
            {
                if(Q.size()<=0) return 0;
                while(Q.size()>1) {
                    ConstType lhs = Q.pull(); assert(Q.size()>0);
                    ConstType rhs = Q.pull();
                    ConstType sum = lhs+rhs;
                    Q.push(sum);
                }
                assert(1==Q.size());
                return Q.pull();
            }

            inline static Type Of(ConstType * const arr)
            {
                assert(arr);
                StaticGEQZSum sum;
                for(size_t i=0;i<N;++i) sum.add(arr[i]);
                return sum();
            }


        private:
            StaticPrioQ< T,N,Sign::Comparator<T> > Q;

        };

    }
}

#endif // !Y_Cameo_StaticGEQZSum_Included
