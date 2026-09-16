
//! \file

#ifndef Y_MKL_Minimize_Golden_Included
#define Y_MKL_Minimize_Golden_Included 1

#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"
#include "y/xml/log.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! Golden Ratio Minimum Improving
        //
        //
        //______________________________________________________________________
        template <typename T> struct Golden
        {

            //__________________________________________________________________
            //
            //! refine local minimum position
            /**
             \param xml output
             \param x   initial coordinates
             \param f   initial values
             \param F   primary function
             */
            //__________________________________________________________________
            static void Step(XML::Log      &xml,
                             Triplet<T>    &x,
                             Triplet<T>    &f,
                             Function<T,T> &F);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename FUNCTION> static inline
            void Step(XML::Log   & xml,
                      FUNCTION   & F,
                      Triplet<T> & x,
                      Triplet<T> & f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return Step(xml,x,f,FW);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_MKL_Minimize_Golden_Included
