#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/utest/memio.hpp"

#include "y/type/destruct.hpp"

using namespace Yttrium;

namespace
{

    class Dummy : public Object
    {
    public:

        Dummy() : Object(), a(0)
        {
        }

        virtual ~Dummy() noexcept
        {
        }

        uint32_t a;

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };


}
Y_UTEST(object)
{
    
    {
        std::cerr << "Testing Slim::Compression" << std::endl;
        size_t last  = 0;
        size_t count = 0;
        for(size_t i=1;i<=Object::Factory::MaxSlimBytes;++i)
        {
            const size_t curr = Object::Factory::SlimCompress(i);
            std::cerr << std::setw(4) << i << " -> " << curr << std::endl;
            if(curr>last)
            {
                last = curr;
                ++count;
            }
        }
        std::cerr << "count = " << count << " / " << Object::Factory::MaxSlimBytes << std::endl;
        std::cerr << std::endl;
    }


    std::cerr << "Metrics:" << std::endl;
    Y_PRINTV(Object::Factory::MaxSlimBytes);
    Y_PRINTV(Object::Factory::MaxFairBytes);
    Y_PRINTV(Object::Factory::MaxVastBytes);
    std::cerr << std::endl;

    UTest::MemIO::Test<Object,1024>( (3*ObjectFactoryType::MaxFairBytes)/2 );



    std::cerr << "Testing Ctor/Dtor" << std::endl;
    {
        Dummy * dummy = 0;
        delete  dummy;

        dummy = new Dummy();
        delete dummy;

        dummy = new Dummy[5];
        delete []dummy;

        void *wksp[4];
        dummy = new (wksp) Dummy();
        Destruct(dummy);
    }
    std::cerr << std::endl;


    Y_PRINTV(ObjectFactory<16>::MinUserBytes);
    Y_PRINTV(ObjectFactory<32>::MinUserBytes);
    Y_PRINTV(ObjectFactory<64>::MinUserBytes);
    Y_PRINTV(ObjectFactory<128>::MinUserBytes);
    Y_PRINTV(ObjectFactory<256>::MinUserBytes);
    Y_PRINTV(ObjectFactory<512>::MinUserBytes);
    Y_PRINTV(ObjectFactory<1024>::MinUserBytes);
    std::cerr << std::endl;

    UTest::MemIO memIO;
    memIO.test<8,Object,512>(10000);



}
Y_UDONE()

