
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

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &self)
        {
            return os << self.value;
        }

        int value;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_hash_map)
{

    HashMap<String,Dummy> hmap;

    {
        const Dummy dum(7);
        Y_CHECK(hmap.insert("hello",dum));
        Y_CHECK(!hmap.insert("hello",dum));
        Y_CHECK(hmap.insert("world",dum));
        Y_CHECK(!hmap.insert("world",dum));
    }
    
    std::cerr << "hmap=" << hmap << std::endl;
    hmap.remap(100);
    std::cerr << "hmap=" << hmap << std::endl;

    {
        const HashMap<String,Dummy> htmp(hmap);
        std::cerr << "htmp=" << htmp << std::endl;
    }



}
Y_UDONE()

