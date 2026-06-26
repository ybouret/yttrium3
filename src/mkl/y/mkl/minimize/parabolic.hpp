//! \file

#ifndef Y_MKL_Minimize_Parabolic_Included
#define Y_MKL_Minimize_Parabolic_Included 1

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
        //! Parabolic hybrid step to pinpoint local minimum
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Parabolic
        {
        public:
            class Code;
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Parabolic();           //!< setup
            virtual ~Parabolic() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! refine local minimum position
            /**
             \param xml output
             \param x   initial coordinates
             \param f   initial values
             \param F   primary function
             */
            void step(XML::Log      &xml,
                      Triplet<T>    &x,
                      Triplet<T>    &f,
                      Function<T,T> &F);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename FUNCTION>   inline
            void step(XML::Log   & xml,
                      FUNCTION   & F,
                      Triplet<T> & x,
                      Triplet<T> & f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return step(xml,x,f,FW);
            }

        private:
            Y_Disable_Copy_And_Assign(Parabolic); //!< discard
            Code * const code;                    //!< inner code
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_MKL_Minimize_Parabolic_Included
