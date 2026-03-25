#include "y/memory/pages.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"
#include "y/libc/block/zeroed.h"
#include "y/libc/defs.h"
#include "y/stream/xmlog.hpp"

using namespace Yttrium;

Y_UTEST(memory_pages)
{

    Core::Rand ran;

    Y_PRINTV(Collectable::NewSize(0x00,100));
    Y_PRINTV(Collectable::NewSize(0x10,100));
    Y_PRINTV(Collectable::NewSize(0x20,100));
    Y_PRINTV(Collectable::NewSize(0x40,100));
    Y_PRINTV(Collectable::NewSize(0x80,100));
    Y_PRINTV(Collectable::NewSize(0xff,100));

    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    {
        Memory::Pages        pages(nucleus,nucleus.access,10);

        void *         p[100];
        const size_t   n = sizeof(p)/sizeof(p[0]);
        pages.cache(n/10);
        std::cerr << "count=" << pages.count() << std::endl;
        for(size_t i=0;i<n;++i)
        {
            p[i] = pages.get(); Y_ASSERT( Y_TRUE == Yttrium_Zeroed(p[i], pages.pageBytes) );
            Random::Fill(ran, (char *)p[i], pages.pageBytes);
        }
        Random::Shuffle(ran,p,n);
        for(size_t i=0;i<n/2;++i)
        {
            pages.put(p[i]);
        }
        std::cerr << "count=" << pages.count() << std::endl;
        pages.gc(0x20);
        std::cerr << "count=" << pages.count() << std::endl;
        for(size_t i=0;i<n/2;++i)
        {
            p[i] = pages.get(); Y_ASSERT( Y_TRUE == Yttrium_Zeroed(p[i], pages.pageBytes) );
            Random::Fill(ran, (char *)p[i], pages.pageBytes);
        }
        for(size_t i=0;i<n;++i)
        {
            pages.put(p[i]);
        }

        bool     verbose = true;
        XML::Log xml(std::cerr,verbose);
        pages.toXML(xml);
    }
    



}
Y_UDONE()


