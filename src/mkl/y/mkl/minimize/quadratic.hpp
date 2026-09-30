
//! \file

#ifndef Y_MKL_Minimize_Quadratic_Included
#define Y_MKL_Minimize_Quadratic_Included 1

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
        //! Base class for steps
        //
        //
        //______________________________________________________________________
        class QuadraticStep
        {
        public:
            static bool Trace;                       //!< tracing results
            explicit QuadraticStep() noexcept; //!< setup
            virtual ~QuadraticStep() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(QuadraticStep); //!< discarded
        };


        //______________________________________________________________________
        //
        //
        //
        //! Quadratic step
        //
        //
        //______________________________________________________________________

        template <typename T>
        class Quadratic : public QuadraticStep
        {
        public:
            class Code;


            explicit Quadratic();
            virtual ~Quadratic() noexcept;

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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //! find local minimum
            /**
             \param xml output
             \param x   initial coordinates
             \param f   initial values
             \param F   primary function
             \param cycles maximum cycles to debug
             */
            T find(XML::Log      &xml,
                   Triplet<T>    &x,
                   Triplet<T>    &f,
                   Function<T,T> &F,
                   const size_t   cycles=0);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename FUNCTION>   inline
            T find(XML::Log   & xml,
                   FUNCTION   & F,
                   Triplet<T> & x,
                   Triplet<T> & f,
                   const size_t cycles = 0)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return find(xml,x,f,FW,cycles);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        private:
            Y_Disable_Copy_And_Assign(Quadratic);
            Code * const code;
        };


    }

}


#endif // !Y_MKL_Minimize_Quadratic_Included

