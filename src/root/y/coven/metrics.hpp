//! \file

#ifndef Y_Coven_Metrics_Included
#define Y_Coven_Metrics_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //______________________________________________________________________
        //
        //
        //
        //! Metrics for a vector space
        //
        //
        //______________________________________________________________________
        class Metrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Metrics(const size_t dims) noexcept; //!< setup \param dims dims > 0
            virtual ~Metrics()                  noexcept; //!< cleanup
            Metrics(const Metrics &)            noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t dimensions; //!< dimensions of space

        private:
            Y_Disable_Assign(Metrics); //!< discarded
        };

    }

}

#endif // !Y_Coven_Metrics_Included
