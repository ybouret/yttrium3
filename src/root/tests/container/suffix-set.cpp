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

		}

		inline virtual ~Dummy() noexcept
		{

		}
		inline Dummy(const Dummy& other) : name(other.name) {}

		const String & key() const noexcept { return name; }

		

		const String name;
	private:
		Y_Disable_Assign(Dummy);
	};
}

Y_UTEST(container_suffix_set)
{
	//SuffixProto<int, int, SuffixSetNode> proto;
	SuffixSet<String, Dummy>  dset;

}
Y_UDONE()

