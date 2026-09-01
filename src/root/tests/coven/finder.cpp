#include "y/coven/finder.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/arc.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_finder)
{
    Core::Rand ran;

    Y_SIZEOF(Coven::Finder);

    const size_t          dims = 4;
    ArcPtr<Coven::Finder> finder = new Coven::Finder(dims);

    CxxArray<int> arr(dims);
    for(size_t i=1;i<=dims;++i)
    {
        for(size_t j=1;j<=dims;++j)
            arr[j] = ran.in<int>(-1,1);
        if(finder->accepts(arr))
            std::cerr << "[+] " << arr << std::endl;
        else
            std::cerr << "[-] " << arr << std::endl;
    }
    Y_PRINTV(finder->size);
    finder->free();
    Y_PRINTV(finder->size);


}
Y_UDONE()


