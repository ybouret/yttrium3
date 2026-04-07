#include "y/object/light/factory.hpp"
#include "y/utest/run.hpp"
#include "y/utest/memio.hpp"
#include "y/core/list/cxx.hpp"

using namespace Yttrium;

namespace
{
    class Node : public LightObject
    {
    public:
        explicit Node(Core::Rand &ran) noexcept :
        value( ran.in<int>(1,10) ),
        next(0), prev(0)
        {
        }

        Node(const Node &node) noexcept :
        value(node.value),
        next(0), prev(0)
        {
        }

        virtual ~Node() noexcept
        {
        }

        const int value;
        Node *    next;
        Node *    prev;

    private:
        Y_Disable_Assign(Node);
    };
}

Y_UTEST(light_object)
{

    Concurrent::Singulet::Verbose = true;
    Core::Rand ran;

    Y_PRINTV(LightObject::Factory::TableSize);
    Y_SIZEOF(LightObject::Factory::Node);


    UTest::MemIO::Test<LightObject,1024,32>(80);

    LightObject::Factory &F = LightObject::Factory::Instance();
    F.writeXML(std::cerr);

    CxxList<Node> list;
    for(size_t i = 100 + ran.in<size_t>(1,1000);i>0;--i)
    {
        if( ran.choice() )
        {
            list.pushTail( new Node(ran) );
        }
        else
        {
            list.pushHead( new Node(ran) );
        }
    }



}
Y_UDONE()


