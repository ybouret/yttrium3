#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/memory/allocator/global.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"


#include "y/memory/small/arena/metrics.hpp"
#include "y/memory/plastic/forge/metrics.hpp"

#include "y/calculus/meta2.hpp"
#include "y/core/meta-max.hpp"

namespace Yttrium
{


#if 0
    template <size_t MAX_SLIM_BYTES>
    struct OMetrics
    {
        static const size_t   MaxSlimBytes = MAX_SLIM_BYTES;
        static const unsigned MaxSlimShift = MetaExactLog2<MaxSlimBytes>::Value; //!< enforce power of two
        static const size_t   MinNumBlocks = Memory::Small::ArenaMetrics::MinNumBlocks;
        static const size_t   MaxNumBlocks = Memory::Small::ArenaMetrics::MaxNumBlocks;
        static const size_t   DataLocation = Memory::Small::ArenaMetrics::DataLocation;

        static const size_t   NumPredicted = DataLocation + MinNumBlocks*MaxSlimBytes;
        static const size_t   MinRawLength = MetaMax<NumPredicted,Memory::Metrics::DefaultBytes>::Value;
        static const size_t   MinUserBytes = MetaNextPowerOfTwo<MinRawLength>::Value;
        static const size_t   UserBlocks   = (MinUserBytes-DataLocation) / MaxSlimBytes;
        typedef typename Core::MetaAccept< (UserBlocks<=MaxNumBlocks) >::Type HasValidSlimBytes;
        static HasValidSlimBytes Check = 1;
        static const size_t MaxFairBytes = MinUserBytes - Memory::Plastic::ForgeMetrics::ReservedSize;
        static const size_t MaxVastBytes = Memory::Metrics::MaxPageBytes;
    };
#endif

}

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



    Y_PRINTV(ObjectFactory<16>::MinUserBytes);
    Y_PRINTV(ObjectFactory<32>::MinUserBytes);
    Y_PRINTV(ObjectFactory<64>::MinUserBytes);
    Y_PRINTV(ObjectFactory<128>::MinUserBytes);
    Y_PRINTV(ObjectFactory<256>::MinUserBytes);
    Y_PRINTV(ObjectFactory<512>::MinUserBytes);
    Y_PRINTV(ObjectFactory<1024>::MinUserBytes);


}
Y_UDONE()

