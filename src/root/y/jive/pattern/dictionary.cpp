
#include "y/jive/pattern/dictionary.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Dictionary:: Dictionary() : DictMap() {}
        Dictionary:: ~Dictionary() noexcept {}

        Dictionary:: Dictionary(const Dictionary &dict) : DictMap(dict)
        {
        }

        void Dictionary:: operator()(const String &key, Pattern * const p)
        {
            const Motif m(p);
            if(!insert(key,p)) throw Specific::Exception("Jive::Dict","multiple '%s'", key.c_str());
        }

        void Dictionary:: operator()(const char * const key, Pattern * const p)
        {
            AutoPtr<Pattern> keep(p);
            const String _(key);
            (*this)(_,keep.yield());
        }

        Pattern * Dictionary:: clone(const String &key)
        {
            const Motif * const m = search(key);
            if(!m) return 0;
            return (**m).clone();
        }


    }

}
