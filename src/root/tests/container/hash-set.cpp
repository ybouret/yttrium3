
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

        Dummy(const Dummy&dum) : name(dum.name) {}

        const String & key() const noexcept
        {
            return name;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &self)
        {
            return os << self.name;
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

    {
        const Dummy dum("hello");
        Node * const node = new ( Object::AcquireZombie<Node>() ) Node(7,dum);
        Y_CHECK( hp.insertNode( node ) );
        std::cerr << hp << std::endl;
    }


}
Y_UDONE()

