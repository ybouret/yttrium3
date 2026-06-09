#include "y/jive/lexical/scanner/code.hpp"


namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            bool     Scanner:: Verbose = false;
            unsigned Scanner:: Aligned = 20;

            Scanner:: ~Scanner() noexcept
            {
                assert(code);
                Destroy(code);
            }

            const Rule & Scanner:: add(Rule * const rule)
            {
                assert(rule);
                assert(code);
                code->add(rule);
                return *rule;
            }

            const String &  Scanner:: key() const noexcept
            {
                return *name;
            }

            const Rule & Scanner:: processing(const Identifier & _name,
                                              const Motif      & _form,
                                              const unsigned     _deed)
            {
                return add( new Rule(_name,_form,_deed,_name,0) );
            }

            Scanner * Scanner:: self() noexcept
            {
                return this;
            }


            const Rule * Scanner:: queryLexicalRule(const String &rid) const noexcept
            {
                for(const Rule *rule=code->rlist.head;rule;rule=rule->next)
                {
                    if(rid == *rule->name) return rule;
                }
                return 0;
            }


            const Pattern & Scanner:: getPattern(const String &rid) const noexcept
            {
                const Rule * const rule = queryLexicalRule(rid); assert(rule);
                return *rule->form;
            }

            bool Scanner:: isMultiple(const String &rid) const noexcept
            {
                return getPattern(rid).multiple();
            }

        }

    }

}

