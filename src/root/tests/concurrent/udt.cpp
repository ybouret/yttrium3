#include "y/concurrent/splitting/udt.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/fake-lock.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{
    static inline bool FoundIn(const Readable<MatrixCoord> &v, const MatrixCoord &p) noexcept
    {
        for(size_t i=v.size();i>0;--i)
        {
            if(p==v[i]) return true;
        }
        return false;
    }
}

Y_UTEST(concurrent_udt)
{
    Concurrent::FakeLock access;
    Vector<MatrixCoord>  coords(WithAtLeast,10000);

    for(size_t n=1;n<=50;++n)
    {
        std::cerr << std::endl << "n=" << n << std::endl;
        const size_t kmax = (n*(n+1))>>1;
        Concurrent:: Splitting:: UpperDiagonalTile udt(1,0,access,n);
        coords.free();
        for(size_t k=1;k<=kmax;++k)
        {
            const MatrixCoord p = udt.coord(k);
            //std::cerr << "\tk = " << std::setw(2) << k << " : " << p << std::endl;
            Y_ASSERT( !FoundIn(coords,p) );
            coords << p;
        }

    }

    Y_SIZEOF( Concurrent:: Splitting:: UpperDiagonalTile);

}
Y_UDONE()

