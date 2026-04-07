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

        inline Dummy(const int v, const double alpha) :
        value(v)
        {
            std::cerr << "+Dummy@" << value << " * " << alpha << std::endl;
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
    static const size_t numBlocks = sizeof(wksp)/BytesPerDummy;
    {
        Memory::AutoBuilt<Dummy> dummy(wksp,numBlocks);
        std::cerr << "#built=" << dummy.numBlocks << std::endl;
    }

    {
        const int v = 7;
        Memory::AutoBuilt<Dummy> dummy(wksp,numBlocks,v);
        std::cerr << "#built=" << dummy.numBlocks << std::endl;
    }

    {
        const int v = 9;
        const double a = 0.1;
        Memory::AutoBuilt<Dummy> dummy(wksp,numBlocks,v,a);
        std::cerr << "#built=" << dummy.numBlocks << std::endl;
    }


    {
        int arr[numBlocks+1] = { 0 };
        for(size_t i=1;i<=numBlocks;++i) arr[i] = (int)i;
        Memory::AutoBuilt<Dummy> dummy(Procedural,wksp,numBlocks,arr);
    }


}
Y_UDONE()

