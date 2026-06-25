
//! \file

#ifndef Y_MKL_Minimize_Included
#define Y_MKL_Minimize_Included 1

#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"
#include "y/xml/log.hpp"

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

            T find(XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F);

            template <typename FUNCTION>   inline
            T find(XML::Log &xml, FUNCTION &F, Triplet<T> &x, Triplet<T> &f )
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return find(xml,x,f,FW);
            }

        private:
            Y_Disable_Copy_And_Assign(Minimizer);
            Code * const code;
            
        };

    }

}

#endif // !Y_MKL_Minimize_Included

