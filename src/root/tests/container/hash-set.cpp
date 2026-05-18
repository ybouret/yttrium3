
#include "y/container/associative/hash/set.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"

using namespace Yttrium;

namespace {


    class Dummy
    {
    public:
        inline Dummy(const char * const id) : name(id)
        {
        }

        ~Dummy() noexcept {}

        const String & key() const noexcept
        {
            return name;
        }

        const String name;

    private:
        Y_Disable_Assign(Dummy);
    };

}

Y_UTEST(container_hash_set)
{

    typedef HashSetNode<String,Dummy> Node;

    HashProto<Node> hp(0);

    hp.free();


}
Y_UDONE()

