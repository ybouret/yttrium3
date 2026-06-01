
#include "y/jive/syntax/grammar.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Grammar:: ~Grammar() noexcept
            {
            }

            Y_Proxy_Impl(Grammar,rules)

            void Grammar:: append(Rule * const rule)
            {
                assert(rule);
                AutoPtr<Rule> guard(rule);
                for(const Rule *mine=rules.head;mine;mine=mine->next)
                {
                    if(*mine->name == *rule->name)
                        throw Specific::Exception(lang->c_str(), "multiple rule [%s]", mine->name->c_str());
                }
                rules.pushTail( guard.yield() );
            }

            const Rule & Grammar:: topLevel() const noexcept
            {
                assert(rules.size>0);
                return *rules.head;
            }

            void Grammar:: topLevel(const Rule &rule) noexcept
            {
                assert( rules.owns(&rule) );
                rules.moveToHead( & Coerce(rule) );
            }

            OutputStream & Grammar:: viz(OutputStream &fp) const
            {
                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    rule->vizSelf(fp);
                }
                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    rule->vizLink(fp);
                }
                return fp;
            }

            void Grammar:: render() const
            {
                const String dotFile = *lang + ".dot";
                Vizible::Render(dotFile,*this);
            }

        }

    }

}
