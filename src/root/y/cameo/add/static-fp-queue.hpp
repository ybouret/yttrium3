
//! \file

#ifndef Y_Cameo_Add_Static_FP_Queue_Included
#define Y_Cameo_Add_Static_FP_Queue_Included 1


#include "y/cameo/add/fp-queue.hpp"
#include "y/container/ordered/static-prio-q.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Summator for SCALAR floating points, STATIC memory
        //
        //
        //______________________________________________________________________
        template <typename T, size_t N>
        class StaticSummator : public FP_QAdd<T,StaticPrioQ< QAdd<T>, N, typename QAdd<T>::Comparator > >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef QAdd<T>                                       Item;         //!< alias
            typedef StaticPrioQ<Item,N,typename Item::Comparator> PQ_Type;      //!< alias
            typedef FP_QAdd<T,PQ_Type>                            SummatorType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit StaticSummator() : SummatorType() {}

            //! cleanup
            inline virtual ~StaticSummator() noexcept {}

            //! duplicate \param other another summator
            inline StaticSummator(const StaticSummator &other) : SummatorType(other) {}

        private:
            Y_Disable_Assign(StaticSummator); //!< discarded
        };

    }

}

#endif // !Y_Cameo_Add_Static_FP_Queue_Included

