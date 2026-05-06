
#include "y/core/htable.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

Y_UTEST(core_htable)
{
    Core::Rand ran;

    Y_PRINTV(Core::HTable::BytesPerSlot);
    Y_PRINTV(Core::HTable::MinTableSize);
    Y_PRINTV(Core::HTable::MaxTableSize);

#if 0
    for(size_t bits=0;bits<=16;++bits)
    {
        size_t size = ran.gen<size_t>(bits);
        std::cerr << size;
        size_t numSlots = Core::HTable::SlotsFor(size);

        std::cerr << " => " << size << " / #slot=" << numSlots;
        std::cerr << std::endl;
    }

    {
        size_t size     = Core::HTable::MaxTableSize;
        size_t numSlots = Core::HTable::SlotsFor(size);
        std::cerr << " => " << size << " / #slot=" << numSlots;

    }
#endif

    Core::HTable table(10);
    Y_PRINTV(table.size());
    Y_PRINTV(table.capacity());
    Vector<size_t> keys;
    int            data = 7;

    keys.free();
    for(size_t i=table.capacity();i>0;--i)
    {
        GEN_KEY:
        {
            const size_t key = ran.gen<size_t>( ran.in<size_t>(0,sizeof(size_t)*8) );
            for(size_t i=1;i<=keys.size();++i)
            {
                if(key == keys[i]) goto GEN_KEY;
            }
            keys << key;
        }
    }
    Y_ASSERT(keys.size()==table.capacity());
    //std::cerr << "keys=" << keys << std::endl;

    for(size_t i=1;i<=keys.size();++i)
    {
        Y_ASSERT(table.insert(keys[i],&data));
    }
    Y_PRINTV(table.size());
    Y_PRINTV(table.capacity());

    table.reserve(4);
    Y_PRINTV(table.size());
    Y_PRINTV(table.capacity());

}
Y_UDONE()

