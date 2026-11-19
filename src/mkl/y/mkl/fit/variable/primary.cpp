#include "y/mkl/fit/variable/primary.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            PrimaryVariable:: ~PrimaryVariable() noexcept
            {
            }

            void PrimaryVariable:: checkIndx() const
            {
                if( indx_ <= 0 ) throw Specific::Exception(CallSign, "invalid index");
            }

            size_t PrimaryVariable:: indx() const noexcept
            {
                assert(indx_>0);
                return indx_;
            }

        }

    }

}


