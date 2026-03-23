#include "y/memory/auto-built.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Dummy
    {
    public:
        inline Dummy() : value(0) {
            std::cerr << "+Dummy@" << value << std::endl;
        }

        inline Dummy(const int v) : value(v)
        {
            std::cerr << "+Dummy@" << value << std::endl;
        }

        inline ~Dummy() noexcept
        {
            std::cerr << "~Dummy@" << value << std::endl;
        }

        const int value;
    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };
}

Y_UTEST(memory_auto_built)
{
    void *wksp[8];
    static const size_t BytesPerDummy = sizeof(Dummy);

    {
        Memory::AutoBuilt<Dummy> dummy(wksp,sizeof(wksp)/BytesPerDummy);
        std::cerr << "#built=" << dummy.numBlocks << std::endl;
    }

    {
        const int v = 7;
        Memory::AutoBuilt<Dummy> dummy(wksp,sizeof(wksp)/BytesPerDummy,v);
        std::cerr << "#built=" << dummy.numBlocks << std::endl;
    }



}
Y_UDONE()

