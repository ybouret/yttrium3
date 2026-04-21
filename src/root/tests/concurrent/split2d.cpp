
#include "y/concurrent/splitting/tile2d.hpp"
#include "y/utest/run.hpp"
#include <typeinfo>

using namespace Yttrium;


namespace {

    template <typename T>
    static inline void Test2D(const T nx, const T ny)
    {
        typedef V2D<T> vertex_t;
        const Concurrent::Splitting::Leap2D<T> leap(vertex_t(1,1), vertex_t(nx,ny) );
        std::cerr << leap.lower << " => " << leap.upper << " : " << leap.items << std::endl;

        for(size_t size=1;size<=8;++size)
        {
            std::cerr << "-- size=" << size << std::endl;
            for(size_t rank=0;rank<size;++rank)
            {
                Concurrent::Splitting::Tile2D<T> tile(size,rank,leap);
                std::cerr << "\t" << tile.c_str() << ": " << tile << std::endl;
                
            }
        }

    }

}

Y_UTEST(concurrent_split2d)
{

    Y_SIZEOF(Concurrent::Splitting::Tile2D<int8_t>);
    Y_SIZEOF(Concurrent::Splitting::Tile2D<uint64_t>);


    Test2D<short>(2,3);
    Test2D<short>(6,6);


}
Y_UDONE()
