
//! \file

#ifndef Y_MKL_Minimize_Included
#define Y_MKL_Minimize_Included 1

#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class Minimizer
        {
        public:
            class Code;
            explicit Minimizer();
            virtual ~Minimizer() noexcept;

            T find(Triplet<T> &x, Triplet<T> &f, Function<T,T> &F);

            template <typename FUNCTION>   inline
            T find(FUNCTION &F, Triplet<T> &x, Triplet<T> &f )
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return find(x,f,FW);
            }

        private:
            Y_Disable_Copy_And_Assign(Minimizer);
            Code * const code;
        public:
            bool & verbose;
        };

    }

}

#endif // !Y_MKL_Minimize_Included

