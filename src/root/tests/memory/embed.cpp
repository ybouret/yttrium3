
#include "y/memory/embed.hpp"
#include "y/utest/run.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

Y_UTEST(memory_embed)
{
    char entry[128];

    uint16_t * a = 0;
    double   * b = 0;

    {
        Memory::Embed embed[] = { Memory::Embed(a,3) };
        size_t  bytes = Memory::Embed::Format(embed,1);
        Core::Display(std::cerr,embed,1) << " => " << bytes << std::endl;
        Memory::Embed::Assign(entry,embed,1);
        Y_CHECK(0!=a);

    }

    {
        a=0;
        Memory::Embed embed[] = { Memory::Embed(a,3), Memory::Embed(b,7) };
        size_t  bytes = Memory::Embed::Format(embed,2);
        Core::Display(std::cerr,embed,2) << " => " << bytes << std::endl;
        Memory::Embed::Assign(entry,embed,2);
        Y_CHECK(0!=a);
        Y_CHECK(0!=b);

    }

}
Y_UDONE()

