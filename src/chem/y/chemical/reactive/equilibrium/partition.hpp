
//! \file

#ifndef Y_Chemical_Partition_Included
#define Y_Chemical_Partition_Included 1

#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/reactive/equilibrium/group.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Independent partitions of connected equilibria
        //
        //
        //______________________________________________________________________
        class Partition
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Partition(XML::Log &,Equilibria & ); //!< setup
            virtual ~Partition() noexcept;                //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            EGroup::List party; //!< prepared equilibria

        private:
            Y_Disable_Copy_And_Assign(Partition); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Partition_Included

