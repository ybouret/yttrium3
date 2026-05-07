
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
            std::cerr << "[+] Dummy(" << value << ")" << std::endl;
        }

        inline virtual ~Dummy() noexcept
        {
            std::cerr << "[!] Dummy(" << value << ")" << std::endl;

        }

        inline Dummy(const Dummy& other) : value(other.value)
        {
            std::cerr << "[*] Dummy(" << value << ")" << std::endl;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &dum)
        {
            return os << dum.value;
        }


        const int value;
    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_suffix_map)
{
    SuffixMap<String,Dummy> dmap;

    {
        const Dummy dum(1);
        Y_ASSERT( dmap.insert("hello",dum) );
        std::cerr << dmap << std::endl;
    }

}
Y_UDONE()

