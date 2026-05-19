
#include "y/jive/pattern/dictionary.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {

        const char * const Dictionary:: CallSign = "Jive::Dictionary";

        Dictionary:: Dictionary() : DictMap() {}
        Dictionary:: ~Dictionary() noexcept {}

        Dictionary:: Dictionary(const Dictionary &dict) : DictMap(dict)
        {
        }

        void Dictionary:: operator()(const String &key, Pattern * const p)
        {
            const Motif m(p);
            if(!insert(key,p)) throw Specific::Exception(CallSign,"multiple '%s'", key.c_str());
        }

        void Dictionary:: operator()(const char * const key, Pattern * const p)
        {
            AutoPtr<Pattern> keep(p);
            const String _(key);
            (*this)(_,keep.yield());
        }

        Pattern * Dictionary:: clone(const String &key) const
        {
            const Motif * const m = search(key);
            if(!m) return 0;
            return (**m).clone();
        }


        void Dictionary:: operator()(const char * const key, const char * const rx)
        {
            const String _(key);
            Pattern * const  p = RegExp::Compile(rx,this);
            (*this)(_,p);
        }

        const Pattern & Dictionary:: operator[](const String &key) const
        {
            const Motif * const m = search(key);
            if(!m) throw Specific::Exception(CallSign,"missing '%s'", key.c_str());
            return **m;
        }

        const Pattern & Dictionary:: operator[](const char * const key) const
        {
            const String _(key);
            return (*this)[_];
        }

    }

}
