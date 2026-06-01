
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Terminal:: ~Terminal() noexcept
            {
            }

            static const char *   TermStyle(const Role role,
                                            const Load load) noexcept
            {

                switch(role)
                {
                    case Semantic:
                        switch(load)
                        {
                            case Standard: return "plain,filled";
                            case Univocal: return "plain,filled,rounded";
                        }
                        break;

                    case Dividing:
                        switch(load)
                        {
                            case Standard: return "dashed,filled";
                            case Univocal: return "dashed,filled,rounded";
                        }
                        break;
                }

                return "plain";
            }

            OutputStream & Terminal:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=box";
                fp << ",style=" << TermStyle(role,load);
                return Endl(fp<<']');
            }

        }

    }

}

