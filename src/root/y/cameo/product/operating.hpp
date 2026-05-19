//! \file

#ifndef Y_Cameo_Product_Strategy_Included
#define Y_Cameo_Product_Strategy_Included 1


#include "y/cameo/product/direct.hpp"
#include "y/cameo/product/raised.hpp"
#include "y/cameo/product/queued.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Product
        {
            //__________________________________________________________________
            //
            //
            //
            //! Find out compute strategy
            //
            //
            //__________________________________________________________________
            template <typename T>
            struct Strategy
            {
                Y_Args_Expose(T,Type); //!< aliases
                static const unsigned UseDirect = ByDirectAPI<MutableType>::IsProper ? 0x01 : 0x00; //!< flag
                static const unsigned UseRaised = ByRaisedAPI<MutableType>::IsProper ? 0x02 : 0x00; //!< flag
                static const unsigned UseQueued = ByQueuedAPI<MutableType>::IsProper ? 0x04 : 0x00; //!< flag
                static const unsigned UseResult = UseDirect | UseRaised | UseQueued;                //!< selection flag
                static const unsigned Index     = IntegerLog2<UseResult>::Value;                    //!< selection index
            };

            template <typename T,const unsigned strategy> struct Selected;

            //! select Direct
            template <typename T> struct Selected<T,0>
            {
                typedef Direct<T> API; //!<alias
            };

            //! select Raised
            template <typename T> struct Selected<T,1>
            {
                typedef Raised<T> API; //!< alias
            };

            //! select Queued
            template <typename T> struct Selected<T,2>
            {
                typedef Queued<T> API; //!< alias
            };

            //! select Operating
            template <typename T>
            struct Operating
            {
                static const unsigned Index = Strategy<T>::Index; //!< alias
                typedef typename Selected<T,Index>::API    Type;  //!< alias
            };

        }

    }

}

#endif // !Y_Cameo_Product_Strategy_Included

