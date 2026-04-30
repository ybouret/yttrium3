#include "y/jive/pattern.hpp"
#include "y/stream/output.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Jive
    {
        Pattern:: ~Pattern() noexcept
        {
            Coerce(uuid) = 0;
            memset( (void*)name, 0, sizeof(name) );
        }

        Pattern:: Pattern(const uint32_t t) noexcept :
        uuid(t),
        name()
        {
            memset( (void*)name, 0, sizeof(name) );
            for(int shift=0,i=0;shift<=24;shift+=8,++i)
            {
                const uint8_t b = uint8_t(uuid>>shift);
                Coerce(name[i]) = (char)b;
            }
        }

        Pattern:: Pattern(const Pattern &p) noexcept :
        Object(),
        uuid(p.uuid),
        name()
        {
            memcpy( (void*)name,p.name,sizeof(name));
        }


        bool Pattern:: frail() const noexcept
        {
            return !sound();
        }

        size_t Pattern:: emitUUID(OutputStream &fp) const
        {
            return fp.cbr(uuid);
        }
    }
}
