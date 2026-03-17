#include "y/memory/moniker.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Dummy
    {
    public:
        Dummy() : value(0)
        {
            std::cerr << "+Dummy@" << value << std::endl;
        }

        Dummy(const int v) : value(v)
        {
            std::cerr << "+Dummy@" << value << std::endl;
        }

        Dummy(const Dummy &_) : value(_.value)
        {
            std::cerr << "*Dummy@" << value << std::endl;
        }

        ~Dummy() noexcept
        {
            std::cerr << "~Dummy@" << value << std::endl;

        }

        const int value;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(memory_moniker)
{
    {
        Memory::Moniker<int> imon;
        std::cerr << imon << std::endl;
    }

    {
        Memory::Moniker<Dummy> mon0;
        const int arg = 5;
        Memory::Moniker<Dummy> mon1(arg);
        std::cerr << mon1->value << std::endl;

    }

}
Y_UDONE()

