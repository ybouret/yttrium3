#include "y/concurrent/splitting/tiles1d.hpp"
#include "y/concurrent/fake-lock.hpp"

#include "y/utest/run.hpp"
#include <typeinfo>

using namespace Yttrium;


namespace {

    template <typename T>
    static inline void Test1D(const T offset, const T length)
    {
        Concurrent::FakeLock sync;
        std::cerr << "Testing for " << typeid(T).name() << ", length=" << length << ", offset=" << offset << std::endl;
        for(size_t size=1;size<=8;++size)
        {
            std::cerr << "-- size=" << size << std::endl;
            for(size_t rank=0;rank<size;++rank)
            {
                Concurrent::Splitting::Tile1D<T> tile(size,rank,sync,offset,length);
                std::cerr << "\t" << tile.c_str() << ": " << tile << std::endl;
            }
            {
                Concurrent::Splitting::Tiles1D<T> tiles(size,sync,offset,length);
                std::cerr << tiles << std::endl;
                tiles.remap(offset+1,length,sync);
            }
        }

    }

}

Y_UTEST(concurrent_split1d)
{

    Test1D<unsigned>(0,10);
    Test1D<int>(1,10);

    Test1D<size_t>(0,6);


}
Y_UDONE()

