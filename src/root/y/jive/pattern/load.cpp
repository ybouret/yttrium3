#include "y/jive/pattern/all.hpp"
#include "y/stream/input.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * Pattern:: Load(InputStream &fp)
        {
            static const char VarName[] = "Pattern";

            const uint32_t uid = fp.cbr<uint32_t>(VarName,"UUID");

            throw Specific::Exception(VarName, "unknown UUID '%s'", FourCC(uid).c_str() );
        }
    }

}
