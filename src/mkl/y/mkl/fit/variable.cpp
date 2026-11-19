#include "y/mkl/fit/variable.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            const char * const Variable:: CallSign = "Fit::Variable";

            Variable:: ~Variable() noexcept {}

            void Variable:: checkName() const
            {
                if(size()<=0)
                    throw Specific::Exception(CallSign, "empty name");
            }

            const String  & Variable:: key() const noexcept
            {
                return *this;
            }

            std::ostream & operator<<(std::ostream &os, const Variable &var)
            {
                os << static_cast<const String&>(var) << '@' << var.indx();
                return os;
            }
        }

    }

}


