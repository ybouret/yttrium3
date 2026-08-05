#include "y/random/in2d.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/v2d.hpp"
#include "y/mkl/complex.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;

Y_UTEST(random_in2d)
{
    Random::ParkMiller ran;

    {
        OutputFile fp("in2d.dat");
        for(size_t i=0;i<100;++i)
        {
            const V2D<float> v = Random::OnCircle< V2D<float> >(ran);
            fp("%g %g\n", v.x, v.y);

            const Complex<double> c = 0.5 * Random::InDisk< Complex<double> >(ran);
            fp("%g %g\n", c.re, c.im);
        }

    }
}
Y_UDONE()

