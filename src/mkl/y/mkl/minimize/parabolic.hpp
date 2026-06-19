//! \file

#ifndef Y_MKL_Minimize_Parabolic_Included
#define Y_MKL_Minimize_Parabolic_Included 1

#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Parabolic
        {
        public:
            class Code;
            explicit Parabolic();
            virtual ~Parabolic() noexcept;

            T step(Triplet<T>    &x,
                   Triplet<T>    &f,
                   Function<T,T> &F);
            
            template <typename FUNCTION>   inline
            T step(FUNCTION &F, Triplet<T> &x, Triplet<T> &f )
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return step(x,f,FW);
            }

        private:
            Y_Disable_Copy_And_Assign(Parabolic);
            Code * const code;
        public:
            bool & verbose;
        };

    }

}

#endif // !Y_MKL_Minimize_Parabolic_Included
