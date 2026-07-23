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

        {
            Concurrent:: Splitting:: UpperDiagonalTile udt(1,0,access,n);
            coords.free();
            for(size_t k=1;k<=kmax;++k)
            {
                const MatrixCoord p = udt.coord(k);
                Y_ASSERT( !FoundIn(coords,p) );
                coords << p;
            }
            Y_ASSERT(kmax==coords.size());
        }

        for(size_t size=1;size<=8;++size)
        {
            std::cerr << "\tsize=" << size << std::endl;
            coords.free();
            for(size_t rank=0;rank<size;++rank)
            {
                Concurrent:: Splitting:: UpperDiagonalTile udt(size,rank,access,n);
                if( udt.isEmpty() ) continue;
                Y_ASSERT(udt.span>0);
                for(size_t i=1;i<=udt.span;++i)
                {
                    Concurrent:: Splitting:: UpperDiagonalSegment s = udt[i];
                    MatrixCoord p = s.start;
                    for(size_t j=s.width;j>0;--j,++p.c)
                    {
                        Y_ASSERT( !FoundIn(coords,p) );
                        coords << p;
                    }
                }
            }
            std::cerr << "\t#coords: " << coords.size() << " / " << kmax << std::endl;
            std::cerr << coords << std::endl;
            Y_ASSERT(kmax==coords.size());
        }


    }

    Y_SIZEOF( Concurrent:: Splitting:: UpperDiagonalTile);

}
Y_UDONE()

