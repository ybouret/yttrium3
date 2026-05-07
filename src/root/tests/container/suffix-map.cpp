
#include "y/container/associative/suffix/map.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

namespace
{
    class Dummy : public CountedObject
    {
    public:
        inline explicit Dummy(const int a) noexcept : value(a)
        {
            std::cerr << "[+] Dummy(" << value << ")" << std::endl;
        }

        inline virtual ~Dummy() noexcept
        {
            std::cerr << "[~] Dummy(" << value << ")" << std::endl;

        }

        inline Dummy(const Dummy& other) : CountedObject(), value(other.value)
        {
            std::cerr << "[*] Dummy(" << value << ")" << std::endl;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &dum)
        {
            return os << dum.value;
        }

        const int value;
    private:
        Y_Disable_Assign(Dummy);
    };
}

#include "y/stream/libc/input.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

Y_UTEST(container_suffix_map)
{
    Core::Rand ran;

    {
        SuffixMap<String,Dummy> dmap;

        {
            const Dummy dum(1);
            Y_ASSERT( dmap.insert("hello",dum) );
            std::cerr << dmap << std::endl;
            Y_CHECK( 0 != dmap.search("hello") );
            Y_CHECK( 1 == dmap.search("hello")->value );
        }
    }

    if(argc>1)
    {
        typedef  ArcPtr<Dummy>  DummyPtr;

        SuffixMap<String,Dummy>    dmap;
        SuffixMap<String,DummyPtr> pmap;
        Vector<String>             keys;

        {
            InputFile fp(argv[1]);
            String line;
            int    value = 0;
            while(fp.gets(line))
            {
                ++value;
                const DummyPtr ptr( new Dummy(value) );
                if(!pmap.insert(line,ptr)) continue;
                Y_ASSERT(dmap.insert(line,*ptr));
                keys << line;
            }
        }

        Y_CHECK(keys.size() == dmap.size() );
        Y_CHECK(keys.size() == pmap.size() );
        Random::Shuffle(ran,keys(),keys.size());
        for(size_t i=1;i<=keys.size();++i)
        {
            const String & key  = keys[i];
            Y_ASSERT( 0 != dmap.search(key) );
            Y_ASSERT( 0 != pmap.search(key) );
            Y_ASSERT( dmap.remove(key) );
            Y_ASSERT( pmap.remove(key) );
            Y_ASSERT( 0 == dmap.search(key) );
            Y_ASSERT( 0 == pmap.search(key) );
            Y_ASSERT( !dmap.remove(key) );
            Y_ASSERT( !pmap.remove(key) );
        }
    }





}
Y_UDONE()

