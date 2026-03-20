#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_wall_time)
{

    System::WallTime chrono;
    std::cerr << "freq=" << chrono.freq << std::endl;
    const uint64_t mark = chrono.Ticks();
    do
    {
        std::cerr << "Time = " << std::setw(15) << chrono.since(mark) << "\r";
    } while( chrono.since(mark) < 0.1L );
    std::cerr << std::endl;
}
Y_UDONE()

