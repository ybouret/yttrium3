
#include "y/jive/lexical/scanner/code.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Scanner::Code:: Code(const Identifier &sid) :
            name(sid),
            rlist(),
            alist(),
            table(sid)
            {
            }

            Scanner::Code:: ~Code() noexcept
            {
            }

            void Scanner::Code::  add(Rule * const rule)
            {
                assert(rule);
                AutoPtr<Rule> guard(rule);
                std::cerr << "-- adding " << rule->name << " to " << name << std::endl;
                noMultiple(*rule);
                table.dispatch(*rule);
                rlist.pushTail( guard.yield() );
            }

            void Scanner::Code:: noMultiple(const Rule & rule) const
            {
                const String &rid = *rule.name;
                for(const Rule *mine=rlist.head;mine;mine=mine->next)
                {
                    if( rid == *mine->name )
                    {
                        throw Specific::Exception(name->c_str(),"mulitple rule '%s'",rid.c_str());
                    }
                }
            }

            Scanner::Code * Scanner:: CreateCode(const Identifier &sid)
            {
                return new Code(sid);
            }
        }

    }

}


