
//! \file

#ifndef Y_MKL_Interpolation_Continuous_Included
#define Y_MKL_Interpolation_Continuous_Included 1

#include "y/container/readable.hpp"
#include "y/memory/type/moniker.hpp"

namespace Yttrium
{

    namespace MKL
    {

        template <typename T, template <class> class INTERP>
        class ContinousInterpolation
        {
        public:
            inline explicit ContinousInterpolation(const Readable<T> &xa,
                                                   const Readable<T> &ya) :
            interp(xa.size()),
            xx(xa),
            yy(ya),
            dy(0)
            {
                assert(xa.size()==ya.size());
            }


            inline virtual ~ContinousInterpolation() noexcept
            {
            }

            inline T operator()(const T x)
            {
                return interp(x,xx,yy,dy);
            }


        private:
            Y_Disable_Copy_And_Assign(ContinousInterpolation);
            INTERP<T>           interp;
            const Readable<T> & xx;
            const Readable<T> & yy;
        public:
            T                   dy;
        };


    }

}

#endif // !Y_MKL_Interpolation_Continuous_Included
