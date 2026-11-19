
//! \file

#ifndef Y_MKL_Fit_PrimaryVariable_Included
#define Y_MKL_Fit_PrimaryVariable_Included 1

#include "y/mkl/fit/variable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class PrimaryVariable : public Variable
            {
            public:
                template <typename NAME> inline
                explicit PrimaryVariable(const NAME &varName, const size_t varIndx) :
                Variable(varName),
                indx_(varIndx)
                {
                    checkIndx();
                }
                virtual ~PrimaryVariable() noexcept;

                virtual size_t indx() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(PrimaryVariable);
                void checkIndx() const;
                const size_t indx_;
            };

           
        }

    }

}


#endif // !Y_MKL_Fit_PrimaryVariable_Included

