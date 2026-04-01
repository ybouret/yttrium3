#include "y/concurrent/member.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_member)
{
    const size_t extent = 100;
    for(size_t size=1;size<=16;++size)
    {
        std::cerr << "-- size=" << size << std::endl;
        size_t travel = 0;
        for(size_t rank=0;rank<size;++rank)
        {
            const Concurrent::Member member(size,rank);
            const size_t length = member.part(extent,travel);
            const size_t offset = travel;
            std::cerr << "\t" << member << " @offset = " << std::setw(4) << offset << " + " << length << std::endl;
        }
    }
}
Y_UDONE()

