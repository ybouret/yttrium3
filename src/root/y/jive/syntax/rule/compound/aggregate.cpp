#include "y/jive/syntax/rule/compound/aggregate.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Aggregate:: ~Aggregate() noexcept
            {
            }

            OutputStream & Aggregate:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=house";
                return Endl(fp << ']');

            }

            Y_Jive_Syntax_Rule_Impl(Aggregate)
            {

            }
        }

    }

}


