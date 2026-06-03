
#include "y/jive/syntax/rule.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            bool Rule::Verbose = false;
            
            const char * Rule:: humanReadableKind() const noexcept
            {
                return HumanReadableKind(kind);
            }

            Rule:: ~Rule() noexcept
            {
            }

            OutputStream & Rule:: vizLink(OutputStream &fp) const
            {
                return fp;
            }

            bool Rule:: isInternal() const noexcept { return IsInternal == kind; }
            bool Rule:: isTerminal() const noexcept { return IsTerminal == kind; }

            OutputStream & Rule:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                vizPpty(fp);
                return Endl(fp<<']');
            }

            OutputStream & Rule:: vizPpty(OutputStream &fp) const
            {
                return fp << ",shape=\"" << vizShape() << "\",style=\"" << vizStyle() << "\"";
            }

        }

    }

}


