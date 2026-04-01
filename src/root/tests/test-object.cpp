#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/memory/allocator/global.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

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

        explicit Dummy() : Object()
        {
        }

        virtual ~Dummy() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };
}
Y_UTEST(object)
{
    Core::Rand     ran;


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

    Y_PRINTV(Object::Factory::MaxSlimBytes);
    Y_PRINTV(Object::Factory::MaxFairBytes);
    Y_PRINTV(Object::Factory::MaxVastBytes);

    Object::Factory &F = Object::Factory::Instance();

    {
        Memory::Allocator & mgr = Memory::Global::Instance();
        size_t  bytes = 0;
        size_t  count = 6000;
        Block  *entry = mgr.acquireAs<Block>(count,bytes);

        for(size_t i=0;i<count;++i)
        {
            entry[i].addr = F.query(entry[i].size=i);
        }
        Random::Shuffle(ran,entry,count);
        for(size_t i=0;i<count;++i)
        {
            F.store(entry[i].addr,entry[i].size);
        }


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
    }

    Dummy * dummy = 0;
    delete  dummy;

    dummy = new Dummy();
    delete dummy;

    dummy = new Dummy[5];
    delete []dummy;

    void *wksp[4];
    dummy = new (wksp) Dummy();
    


}
Y_UDONE()

