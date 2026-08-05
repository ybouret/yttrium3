
#include "y/random/in3d.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/v3d.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;

Y_UTEST(random_in3d)
{
    Random::ParkMiller ran;

    {
        OutputFile fp("in2d.dat");
        for(size_t i=0;i<100;++i)
        {
            const V3D<float> v = Random::OnSphere< V3D<float> >(ran);
            fp("%g %g %g\n", v.x, v.y, v.z);

            const V3D<double>  c = 0.5 * Random::InBall< V3D<double> >(ran);
            fp("%g %g %g\n", c.x, c.y, c.z);
        }

    }
}
Y_UDONE()

