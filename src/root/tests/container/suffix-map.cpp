
#include "y/container/associative/suffix/map.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

namespace
{
    class Dummy
    {
    public:
        inline explicit Dummy(const int a) noexcept : value(a)
        {

        }

        inline virtual ~Dummy() noexcept
        {

        }

        inline Dummy(const Dummy& other) : value(other.value) {}


        const int value;
    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_suffix_map)
{
    SuffixMap<String,Dummy> dmap;
}
Y_UDONE()

