#include "y/mkl/root/zbis.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    static size_t calls = 0;
    template <typename T> static inline
    T Id(const T &x) { ++calls; return x; }

    template <typename T> static inline
    T F3(const T &x) { ++calls; return T(1)+x+x*x-x*x*x; }

    template <typename T> static inline
    void solve()
    {
        std::cerr << "-- Solving" << std::endl;
        const T xlo(-1.2f);
        const T xhi(2.3f);
        Triplet<T> xx = { xlo, -1.0f, xhi };
        Triplet<T> ff = { Id(xx.a), -1.0f, Id(xx.c) };
        ZBis<T>    zbis;
        ZRid<T>    zrid;

        calls = 0;
        const T xb0 = zbis(Id<T>,xx,ff);
        std::cerr << "xb0=" << xb0 << ", #calls=" << calls << std::endl;

        calls = 0;
        xx.a = xlo;      xx.c = xhi;
        ff.a = Id(xx.a); ff.c = Id(ff.c);
        const T xr0 = zrid(Id<T>,xx,ff);
        std::cerr << "xr0=" << xr0 << ", #calls=" << calls << std::endl;


        calls = 0;
        xx.a = xlo;      xx.c = xhi;
        ff.a = F3(xx.a); ff.c = F3(xx.c);
        const T xb3 = zbis(F3<T>,xx,ff);
        std::cerr << "xb3=" << xb3 << ", #calls=" << calls << std::endl;


        calls = 0;
        xx.a = xlo;      xx.c = xhi;
        ff.a = F3(xx.a); ff.c = F3(xx.c);
        const T xr3 = zrid(F3<T>,xx,ff);
        std::cerr << "xr3=" << xr3 << ", #calls=" << calls << std::endl;



    }
}

Y_UTEST(zroot)
{
    solve<float>();
    solve< XReal<double> >();

}
Y_UDONE()

