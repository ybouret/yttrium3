#include "y/concurrent/splitting/udt.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/fake-lock.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_udt)
{
    Concurrent::FakeLock access;

    for(size_t n=1;n<=4;++n)
    {
        std::cerr << std::endl << "n=" << n << std::endl;
        const size_t kmax = (n*(n+1))>>1;
        Concurrent:: Splitting:: UpperDiagonalTile udt(1,0,access,n);
        for(size_t k=1;k<=kmax;++k)
        {
            const MatrixCoord p = udt.coord(k);
            std::cerr << "\tk = " << std::setw(2) << k << " : " << p << std::endl;
        }

    }

    Y_SIZEOF( Concurrent:: Splitting:: UpperDiagonalTile);

}
Y_UDONE()

