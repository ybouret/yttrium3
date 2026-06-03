
#include "y/jive/syntax/rule/compound/alternate.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Alternate:: ~Alternate() noexcept
            {
            }

            OutputStream & Alternate:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=egg";
                return Endl(fp << ']');
            }

            Y_Jive_Syntax_Rule_Impl(Alternate)
            {
                
            }
        }

    }

}


