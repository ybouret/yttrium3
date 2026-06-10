
//! \file

#ifndef Y_MKL_Statistic_Average_Included
#define Y_MKL_Statistic_Average_Included 1

#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Statistics
        {

            struct Average
            {
                template <typename T, typename ITERATOR> static inline
                T OfRange(ITERATOR curr, size_t size, Cameo::Addition<T> &xadd)
                {
                    if(size<=0)
                        return 0;
                    const T denom = (T) size;
                    xadd.ldz();
                    while(size-- > 0)
                        xadd << *(curr++);
                    return xadd()/denom;
                }

                template <typename T> static inline
                T Of(const T data[], const size_t size, Cameo::Addition<T> &xadd)
                {
                    return OfRange(data,size,xadd);
                }

                template <typename SEQUENCE> static inline
                typename SEQUENCE::Type Of(SEQUENCE &seq, Cameo::Addition<typename SEQUENCE::MutableType> &xadd)
                {
                    return OfRange(seq.begin(),seq.size(), xadd);
                }

            };
        }
    }
}

#endif // !Y_MKL_Statistic_Average_Included

