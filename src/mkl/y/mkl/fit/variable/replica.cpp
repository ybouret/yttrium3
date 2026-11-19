
#include "y/mkl/fit/variable/replica.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            
            ReplicaVariable:: ~ReplicaVariable() noexcept
            {
            }


            Variable * ReplicaVariable:: CheckVariable(const Variable &var)
            {
                if(var.quantity()<=0)
                    throw Specific::Exception(Variable::CallSign, "not a dynamic variable");
                return & Coerce(var);
            }



            size_t ReplicaVariable:: indx() const noexcept
            {
                return ptr->indx();
            }

        }
    }
}

