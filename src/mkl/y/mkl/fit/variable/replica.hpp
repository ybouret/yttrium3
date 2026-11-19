
//! \file

#ifndef Y_MKL_Fit_ReplicaVariable_Included
#define Y_MKL_Fit_ReplicaVariable_Included 1

#include "y/mkl/fit/variable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class ReplicaVariable : public Variable
            {
            public:
                template <typename NAME> inline
                explicit ReplicaVariable(const NAME     &varName,
                                         const Variable &variable) :
                Variable(varName),
                ptr( CheckVariable(variable) )
                {
                }

                virtual ~ReplicaVariable() noexcept;

                virtual size_t indx() const noexcept;

                static Variable * CheckVariable(const Variable &);

            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable);
                const Variable::Pointer ptr;
            };

         


        }


    }

}
#endif // !Y_MKL_Fit_ReplicaVariable_Included

