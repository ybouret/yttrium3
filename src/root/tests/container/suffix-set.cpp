#include "y/container/associative/suffix/set.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

namespace
{
	class Dummy : public CountedObject
	{
	public:
		inline explicit Dummy(const char* const id) : name(id)
		{
            std::cerr << "[+] Dummy(" << name << ")" << std::endl;
		}

		inline virtual ~Dummy() noexcept
		{
            std::cerr << "[~] Dummy(" << name << ")" << std::endl;
        }

        inline Dummy(const Dummy& other) :
        CountedObject(),
        name(other.name)
        {
            std::cerr << "[*] Dummy(" << name << ")" << std::endl;
        }

		const String & key() const noexcept { return name; }

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &dum)
        {
            return os << dum.name;
        }



		const String name;
	private:
		Y_Disable_Assign(Dummy);
	};
}

#include "y/stream/libc/input.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

Y_UTEST(container_suffix_set)
{

    Core::Rand ran;

    {
        SuffixSet<String,Dummy> dset;

        {
            const Dummy dum("hello");
            Y_CHECK(  dset.insert(dum) );
            Y_CHECK( !dset.insert(dum) );
            std::cerr << dset << std::endl;
            Y_CHECK( 0!=dset.search("hello") );
            Y_CHECK( "hello" == dset.search("hello")->name );
        }
    }

    if(argc>1)
    {
        typedef Keyed<String,ArcPtr<Dummy> > DummyPtr;

        SuffixSet<String,Dummy>    dset;
        SuffixSet<String,DummyPtr> pset;
        Vector<String>             keys;

        {
            InputFile fp(argv[1]);
            String line;
            while(fp.gets(line))
            {
                const DummyPtr ptr( new Dummy(line.c_str()) );
                if(!pset.insert(ptr)) continue;
                Y_ASSERT(dset.insert(*ptr));
                keys << line;
            }
        }

        Y_CHECK(keys.size() == dset.size() );
        Y_CHECK(keys.size() == pset.size() );

        { const SuffixSet<String,Dummy>    cpy(dset); Y_ASSERT(cpy.size() == dset.size()); }
        { const SuffixSet<String,DummyPtr> cpy(pset); Y_ASSERT(cpy.size() == pset.size()); }

        Random::Shuffle(ran,keys(),keys.size());
        for(size_t i=1;i<=keys.size();++i)
        {
            const String & key  = keys[i];
            Y_ASSERT( 0 != dset.search(key) );
            Y_ASSERT( 0 != pset.search(key) );
            Y_ASSERT( dset.remove(key) );
            Y_ASSERT( pset.remove(key) );
            Y_ASSERT( 0 == dset.search(key) );
            Y_ASSERT( 0 == pset.search(key) );
            Y_ASSERT( !dset.remove(key) );
            Y_ASSERT( !pset.remove(key) );
        }
    }

}
Y_UDONE()

