#include "y/stream/identifiers.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/exception.hpp"

namespace Yttrium
{

    const char * const Identifiers:: CallSign = "Identifiers";


    class Identifiers:: Code : public CountedObject, public HashSet<String,Identifier>
    {
    public:
        inline explicit Code() : CountedObject(), HashSet<String, Identifier>() {}
        inline virtual ~Code() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Code);
    };



    Identifiers:: ~Identifiers() noexcept
    {
        if(code->liberate()) Destroy(code);
    }

    Identifiers:: Identifiers() : code( new Code() )
    {
        code->withhold();
    }

    Identifiers:: Identifiers(const Identifiers &other)  noexcept :
    code(other.code)
    {
        code->withhold();
    }


    //void Identifiers:: record(const Identifier &id)
    //{
    //    assert(code);
    //    if( !code->search(*id) && !code->insert(id)) throw Specific::Exception(CallSign,"failed to insert missing '%s'", id->c_str());
    //}

    const Identifier  Identifiers:: record(const Identifier &id)
    {
        assert(code);
        (void) code->insert(id);
        return id;
    }


    const Identifier Identifiers:: record(const String &s)
    {
        assert(code);
        {
            const Identifier * const pid = code->search(s);
            if(pid) return *pid;
        }

        const Identifier id(s);
        if(!code->insert(id)) throw Specific::Exception(CallSign,"failed to insert missing '%s'", id->c_str());
        return id;

    }

    const Identifier Identifiers:: record(const char * const s)
    {
        const String _(s); return record(_);
    }



    const Identifier * Identifiers:: search(const String &key) const
    {
        assert(code);
        return code->search(key);
    }



}
