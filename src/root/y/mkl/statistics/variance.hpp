

//! \file

#ifndef Y_MKL_Statistic_Variance_Included
#define Y_MKL_Statistic_Variances_Included 1

#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Statistics
        {

            struct Variance
            {
                template <typename T, typename ITERATOR> static inline
                T OfRange(ITERATOR curr, size_t size, T average, Cameo::Addition<T> &xadd)
                {
                    if(size<=1)
                        return 0;
                    const T denom = (T) size;
                    xadd.ldz();
                    while(size-- > 0)
                    {
                        const T delta = average - *(curr++);
                        const T delsq = delta*delta;
                        xadd << delsq;
                    }
                    return xadd()/denom;
                }

                template <typename T> static inline
                T Of(const T data[], const size_t size, T average, Cameo::Addition<T> &xadd)
                {
                    return OfRange(data,size,average,xadd);
                }

                template <typename SEQUENCE> static inline
                typename SEQUENCE::Type Of(SEQUENCE &seq, typename SEQUENCE::Type average, Cameo::Addition<typename SEQUENCE::MutableType> &xadd)
                {
                    return OfRange(seq.begin(),seq.size(),average,xadd);
                }

            };
        }
    }
}

#endif // !Y_MKL_Statistic_Variance_Included

