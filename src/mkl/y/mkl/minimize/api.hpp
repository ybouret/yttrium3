
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

        //______________________________________________________________________
        //
        //
        //
        //! Control of algorithm
        //
        //
        //______________________________________________________________________
        struct Minimize
        {
            //__________________________________________________________________
            //
            //
            //! How to process input data
            //
            //__________________________________________________________________
            enum Process
            {
                Direct, //!< already at local minimum
                Inside, //!< bracket in [a:c]
                Expand, //!< exprand from [a:b]
            };

            //__________________________________________________________________
            //
            //
            //! convergence criterion
            //
            //__________________________________________________________________
            enum Criterion
            {
                Standard, //!< converged function values
                Pedantic  //!< standard and converged successive estimations
            };

            //__________________________________________________________________
            //
            //
            //! engine to run minimization
            //
            //__________________________________________________________________
            template <typename T>
            class Engine
            {
            public:
                class Code;
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Engine();
                virtual ~Engine() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! find local minimum from a given configuration
                /**
                 \param xml output
                 \param how how to process input
                 \param x   initial coordinates
                 \param f   initial values
                 \param F   primary function
                 \param win criterion
                 \return minimum x
                 */
                T find(XML::Log    &   xml,
                       const Process   how,
                       Triplet<T>    & x,
                       Triplet<T>    & f,
                       Function<T,T> & F,
                       const Criterion win);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                template <typename FUNCTION>   inline
                T find(XML::Log        & xml,
                       FUNCTION        & F,
                       const Process     how,
                       Triplet<T>      & x,
                       Triplet<T>      & f,
                       const Criterion   win)
                {
                    Wrapper1D<T,T,FUNCTION> FW(F);
                    return find(xml,how,x,f,FW,win);
                }

            private:
                Y_Disable_Copy_And_Assign(Engine);
                Code * const code;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };

        };


    }

}

#endif // !Y_MKL_Minimize_Included

