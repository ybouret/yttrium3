#include "y/ink/broker.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    class Ops
    {
    public:

        inline Ops() noexcept {}
        inline ~Ops() noexcept {}

        void show(Ink::Tile &tile, const Ink::Area &area)
        {
            Y_Giant_Lock();
            std::cerr << "show  " << tile.c_str() << " : " << tile << " of " << area.w << "x" << area.h << std::endl;
        }

        void show1(Ink::Tile &tile, const Ink::Area &area, const String &name)
        {
            Y_Giant_Lock();
            std::cerr << "show  " << name << " as " << tile.c_str() << " : " << tile << " of " << area.w << "x" << area.h << std::endl;
        }


    private:
        Y_Disable_Copy_And_Assign(Ops);
    };
}

Y_UTEST(broker)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    Ink::Broker seq(seqEngine);
    Ink::Broker par(parEngine);
    std::cerr << seq->callSign() << std::endl;
    seq();

    std::cerr << par->callSign() << std::endl;
    par();
    std::cerr << std::endl;


    Ops ops;

    const Ink::Area area(6,5);
    std::cerr << seq->callSign() << std::endl;
    seq(area, ops, & Ops::show);
    std::cerr << par->callSign() << std::endl;
    par(area, ops, & Ops::show);
    std::cerr << std::endl;

    {
        const String name = seq->callSign();
        seq(area, ops, & Ops::show1, name);
    }

    {
        const String name = par->callSign();
        par(area, ops, & Ops::show1, name);
    }



}
Y_UDONE()

