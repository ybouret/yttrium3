
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

            //__________________________________________________________________
            //
            //
            //
            //! compute Average with Cameo
            //
            //
            //__________________________________________________________________
            struct Average
            {
                //! generic range computation
                /**
                 \param curr initial iterator
                 \param size number of items
                 \param xadd cameo addition
                 \return average of the range
                 */
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

                //! legacy array average
                /**
                 \param data first item
                 \param size number of items
                 \param xadd cameo addition
                 \return average of array
                 */
                template <typename T> static inline
                T Of(const T data[], const size_t size, Cameo::Addition<T> &xadd)
                {
                    return OfRange(data,size,xadd);
                }

                //! sequence average
                /**
                 \param seq  sequence with begin() and size()
                 \param xadd cameo addition
                 \return average of sequence
                 */
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

