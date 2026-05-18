//! \file

#ifndef Y_Cameo_Sum_Queued
#define Y_Cameo_Sum_Queued 1


#include "y/cameo/sum/queued-common.hpp"
#include "y/container/ordered/prio-q.hpp"

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
            //! Summator for SCALAR floating points, dynamic
            //
            //
            //______________________________________________________________________
            template <typename T>
            class Queued: public QueuedCode<T,PriorityQ< QAdd<T>, typename QAdd<T>::Comparator > >
            {
            public:
                //__________________________________________________________________
                //
                //
                // Definitions
                //
                //__________________________________________________________________
                typedef QAdd<T>                                   Item; //!< alias
                typedef PriorityQ<Item,typename Item::Comparator> Prio; //!< alias
                typedef QueuedCode<T,Prio>                        Code; //!< alias

                //__________________________________________________________________
                //
                //
                // C++
                //
                //__________________________________________________________________

                //! setup empty
                inline explicit Queued() : Code() {}

                //! setup \param minCapacity minimal capacity
                inline explicit Queued(const size_t minCapacity) : Code(minCapacity) {}

                //! cleanup
                inline virtual ~Queued() noexcept {}

                //! duplicate \param other antother summatro
                inline Queued(const Queued &other) : Code(other) {}

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Sum::Queued";
                }

            private:
                Y_Disable_Assign(Queued); //!< discarded
            };

        }
        
    }

}

#endif // !Y_Cameo_Sum_Queued

