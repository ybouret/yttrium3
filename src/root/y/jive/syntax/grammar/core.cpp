
#include "y/jive/syntax/grammar/core.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            CoreGrammar:: ~CoreGrammar() noexcept
            {
            }

            Y_Proxy_Impl(CoreGrammar,rules)

            void CoreGrammar:: append(Rule * const rule)
            {
                assert(rule);
                AutoPtr<Rule> guard(rule);
                if(frozen) throw Specific::Exception(lang->c_str(), "frozen: cannot append <%s>", rule->name->c_str());

                for(const Rule *mine=rules.head;mine;mine=mine->next)
                {
                    if(*mine->name == *rule->name)
                        throw Specific::Exception(lang->c_str(), "multiple rule [%s]", mine->name->c_str());
                }
                rules.pushTail( guard.yield() );
            }

            const Rule & CoreGrammar:: topLevel() const noexcept
            {
                assert(rules.size>0);
                return *rules.head;
            }

            void CoreGrammar:: topLevel(const Rule &rule) noexcept
            {
                assert( rules.owns(&rule) );
                rules.moveToHead( & Coerce(rule) );
            }

            OutputStream & CoreGrammar:: viz(OutputStream &fp) const
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

            void CoreGrammar:: render() const
            {
                const String dotFile = *lang + ".dot";
                Vizible::Render(dotFile,*this);
            }

            String * CoreGrammar:: MakeName(const Rule *arr[], const size_t num, const char sep)
            {
                assert(arr);
                assert(num>1);
                AutoPtr<String> pS = new String();
                String         &s  = *pS;
                s << '(';
                assert(arr[0]);
                s += *(arr[0]->name);
                for(size_t i=1;i<num;++i) {
                    s += sep;
                    s += *(arr[i]->name);
                }
                s << ')';
                return pS.yield();
            }

          


        }

    }

}
