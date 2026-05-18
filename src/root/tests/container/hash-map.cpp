
#include "y/container/associative/hash/map.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

namespace {

    class Dummy
    {
    public:
        inline Dummy(const int x) : value(x) {}
        inline Dummy(const Dummy &dum) : value(dum.value) {}
        inline ~Dummy() noexcept {}

        int value;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_hash_map)
{

    HashMap<String,Dummy> hmap;

    const Dummy dum(7);
    Y_CHECK(hmap.insert("hello",dum));
    Y_CHECK(!hmap.insert("hello",dum));


}
Y_UDONE()

