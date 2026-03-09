#include "y/utest/driver.hpp"
#include <cassert>
#include <cstring>

namespace Yttrium
{
    const char * const UTest::CallSign = "UTest";

    UTest:: UTest(const char * const n,
                  Proc const         p) noexcept :
    name(n),
    proc(p)
    {
        assert(0!=name);
        assert(0!=proc);
    }



    UTest:: ~UTest() noexcept
    {
    }

    const UTest * UTest:: Search(const char * const  name,
                                 const UTest * const test,
                                 const size_t        size) noexcept
    {
        assert(0!=name);
        assert(0!=test);
        assert(size>0);

        for(size_t i=0;i<size;++i)
        {
            const UTest * const t = &test[i];

        }
        return 0;
    }
}
