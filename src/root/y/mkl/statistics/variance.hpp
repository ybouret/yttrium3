

//! \file

#ifndef Y_MKL_Statistic_Variance_Included
#define Y_MKL_Statistic_Variance_Included 1

#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Statistics
        {

            //__________________________________________________________________
            //
            //
            //
            //! compute Variance with Cameo
            //
            //
            //__________________________________________________________________
            struct Variance
            {
                //! generic range computationg
                /**
                 \param curr    initial iterator
                 \param size    number of items
                 \param average pre-computed average
                 \param xadd    cameo addition
                 \return variance of the range
                 */
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

                //! legacy array variance
                /**
                 \param data    first item
                 \param size    number of items
                 \param average pre-computed average
                 \param xadd     cameo addition
                 \return variance of array
                 */
                template <typename T> static inline
                T Of(const T data[], const size_t size, T average, Cameo::Addition<T> &xadd)
                {
                    return OfRange(data,size,average,xadd);
                }


                //! sequence variance
                /**
                 \param seq     sequence with begin() and size()
                 \param average pre-computed average
                 \param xadd    cameo addition
                 \return variance of sequence
                 */
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

