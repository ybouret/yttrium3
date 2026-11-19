
//! \file

#ifndef Y_MKL_Interpolation_Continuous_Included
#define Y_MKL_Interpolation_Continuous_Included 1

#include "y/container/readable.hpp"
#include "y/memory/type/moniker.hpp"

namespace Yttrium
{

    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! T ransform data into contiuous function
        //
        //
        //______________________________________________________________________
        template <typename T, template <class> class INTERP>
        class ContinuousInterpolation
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param xa persistent abscissae \param ya persisten ordinates
            inline explicit ContinuousInterpolation(const Readable<T> &xa,
                                                    const Readable<T> &ya) :
            interp(xa.size()),
            xx(xa),
            yy(ya),
            dy(0)
            {
                assert(xa.size()==ya.size());
            }

            //! cleanu
            inline virtual ~ContinuousInterpolation() noexcept
            {
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param x abscissa guest \return interpolated value
            inline T operator()(const T x)
            {
                return interp(x,xx,yy,dy);
            }


        private:
            Y_Disable_Copy_And_Assign(ContinuousInterpolation); //!< discared
            INTERP<T>           interp; //!< inner interpolation method
            const Readable<T> & xx;     //!< abscissae
            const Readable<T> & yy;     //!< ordinates
        public:
            T                   dy;     //!< last error estimate
        };


    }

}

#endif // !Y_MKL_Interpolation_Continuous_Included
