
#include "y/jive/pattern/logic/logic.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Logic:: ~Logic() noexcept
        {
        }


        Logic:: Logic(const uint32_t t) noexcept : Pattern(t), Patterns()
        {
        }

        Logic:: Logic(const Logic &other) : Pattern(other), Patterns(other)
        {
        }

        size_t Logic:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res       += fp.vbr(size);
            for(const Pattern *p=head;p;p=p->next)
                res += p->serialize(fp);
            return res;
        }

        void Logic:: load(InputStream &fp)
        {
            const size_t num = fp.vbr<size_t>("Jive::Logic","size");
            for(size_t i=0;i<num;++i)
                pushTail( Load(fp) );
        }


    }

}
