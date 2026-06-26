
//! \file

#ifndef Y_MKL_Minimize_Bracket_Included
#define Y_MKL_Minimize_Bracket_Included 1

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
        //! Bracketing algorithm
        //
        //
        //______________________________________________________________________
        struct Bracket
        {

            //! bracket minimum in (x.a,f.a) (x.c,f.c)
            /**
             \param xml output
             \param x   initial coordinates
             \param f   initial values
             \param F   primary function
             \return true iff local minimum, false iff global minimum on one side
             */
            template <typename T> static
            bool Inside( XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F);

        };

    }
    
}

#endif // !Y_MKL_Minimize_Bracket_Included

