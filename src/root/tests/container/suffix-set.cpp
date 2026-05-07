#include "y/container/associative/suffix/set.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

namespace
{
	class Dummy
	{
	public:
		inline explicit Dummy(const char* const id) : name(id)
		{
            std::cerr << "[+] Dummy(" << name << ")" << std::endl;
		}

		inline virtual ~Dummy() noexcept
		{
            std::cerr << "[~] Dummy(" << name << ")" << std::endl;
        }

        inline Dummy(const Dummy& other) : name(other.name)
        {
            std::cerr << "[*] Dummy(" << name << ")" << std::endl;
        }

		const String & key() const noexcept { return name; }

		

		const String name;
	private:
		Y_Disable_Assign(Dummy);
	};
}

Y_UTEST(container_suffix_set)
{
	SuffixSet<String,Dummy>  dset;

    {
        const Dummy dum("hello");
        Y_CHECK(  dset.insert(dum) );
        Y_CHECK( !dset.insert(dum) );

    }

}
Y_UDONE()

