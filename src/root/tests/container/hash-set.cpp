
#include "y/container/associative/hash/set.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"
#include "y/pointer/keyed.hpp"

using namespace Yttrium;

namespace {


    class Dummy : public CountedObject
    {
    public:
        typedef Keyed<String,ArcPtr<Dummy>> Pointer;

        inline Dummy(const char * const id) : name(id)
        {
        }

        ~Dummy() noexcept {}

        Dummy(const Dummy&dum) : CountedObject(), name(dum.name) {}

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

    HashSet<String,Dummy>          hset;
    HashSet<String,Dummy::Pointer> pset;
    {
        const Dummy dum("hello");
        Y_CHECK(hset.insert(dum));
        Y_CHECK(!hset.insert(dum));

    }
    std::cerr << "hset=" << hset << std::endl;

    {
        const Dummy::Pointer p( new Dummy("world") );
        Y_CHECK( pset.insert(p));
        Y_CHECK(!pset.insert(p));
    }
    std::cerr << "pset=" << pset << std::endl;

    {
        const HashSet<String,Dummy> htmp(hset);
        std::cerr << "htmp=" << htmp << std::endl;
    }

    {
        const HashSet<String,Dummy::Pointer> ptmp(pset);
        std::cerr << "ptmp=" << ptmp << std::endl;
    }



}
Y_UDONE()

