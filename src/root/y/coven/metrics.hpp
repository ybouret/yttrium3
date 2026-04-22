//! \file

#ifndef Y_Coven_Metrics_Included
#define Y_Coven_Metrics_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Coven
    {

        class Metrics
        {
        public:
            explicit Metrics(const size_t dims) noexcept; //!< setup \param dims dims > 0
            virtual ~Metrics()                  noexcept; //!< cleanup
            Metrics(const Metrics &)            noexcept; //!< duplicate

            const size_t dimensions;

        private:
            Y_Disable_Assign(Metrics);
        };

    }

}

#endif // !Y_Coven_Metrics_Included
