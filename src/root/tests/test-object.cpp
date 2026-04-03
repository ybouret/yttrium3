#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/memory/allocator/global.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"


using namespace Yttrium;

namespace
{
    struct Block
    {
        void * addr;
        size_t size;
    };



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
    Core::Rand     ran;

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

    Object::Factory &F = Object::Factory::Instance();

    {
        Memory::Allocator & mgr = Memory::Global::Instance();
        size_t  bytes = 0;
        size_t  count = (3*ObjectFactoryType::MaxFairBytes)/2;
        Block  *entry = mgr.acquireAs<Block>(count,bytes);

        (std::cerr << "Testing Object I/O with up to " << count << " bytes" << std::endl).flush();

        for(size_t i=0;i<count;++i)
        {
            entry[i].addr = F.query(entry[i].size=i);
        }
        Random::Shuffle(ran,entry,count);
        for(size_t i=0;i<count;++i)
        {
            F.store(entry[i].addr,entry[i].size);
        }


        (std::cerr << "Testing Allocator I/O with up to " << count << " bytes" << std::endl).flush();
        for(size_t i=0;i<count;++i)
        {
            entry[i].addr = F.acquire(entry[i].size=i);
            Y_ASSERT(0!=entry[i].addr);
            Y_ASSERT(entry[i].size>0);
        }
        Random::Shuffle(ran,entry,count);

        for(size_t i=0;i<count;++i)
        {
            F.release(entry[i].addr,entry[i].size);
        }


        mgr.releaseAs(entry,count,bytes);
        std::cerr << std::endl;
    }

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
    }
    std::cerr << std::endl;


    Y_PRINTV(ObjectFactory<16>::MinUserBytes);
    Y_PRINTV(ObjectFactory<32>::MinUserBytes);
    Y_PRINTV(ObjectFactory<64>::MinUserBytes);
    Y_PRINTV(ObjectFactory<128>::MinUserBytes);
    Y_PRINTV(ObjectFactory<256>::MinUserBytes);
    Y_PRINTV(ObjectFactory<512>::MinUserBytes);
    Y_PRINTV(ObjectFactory<1024>::MinUserBytes);


}
Y_UDONE()

