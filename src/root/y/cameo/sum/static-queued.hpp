
//! \file

#ifndef Y_Cameo_Sum_Static_Queued
#define Y_Cameo_Sum_Static_Queued 1


#include "y/cameo/sum/queued-common.hpp"
#include "y/container/ordered/static-prio-q.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {

            //______________________________________________________________________
            //
            //
            //
            //! Summator for SCALAR floating points, static
            //
            //
            //______________________________________________________________________
            template <typename T, size_t N>
            class StaticQueued: public QueuedCode<T,StaticPrioQ< QAdd<T>, N, typename QAdd<T>::Comparator > >
            {
            public:
                //__________________________________________________________________
                //
                //
                // Definitions
                //
                //__________________________________________________________________
                typedef QAdd<T>                                       Item; //!< alias
                typedef StaticPrioQ<Item,N,typename Item::Comparator> Prio; //!< alias
                typedef QueuedCode<T,Prio>                            Code; //!< alias

                //__________________________________________________________________
                //
                //
                // C++
                //
                //__________________________________________________________________

                //! setup empty
                inline explicit StaticQueued() : Code() {}

                //! setup \param minCapacity minimal capacity
                inline explicit StaticQueued(const size_t minCapacity) : Code(minCapacity) {}

                //! cleanup
                inline virtual ~StaticQueued() noexcept {}

                //! duplicate \param other antother summatro
                inline StaticQueued(const StaticQueued &other) : Code(other) {}

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Sum::StaticQueued";
                }

            private:
                Y_Disable_Assign(StaticQueued); //!< discarded
            };

        }

    }

}

#endif // !Y_Cameo_Sum_Static_Queued

