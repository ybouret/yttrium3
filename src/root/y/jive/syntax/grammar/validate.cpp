#include "y/jive/syntax/grammar.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            namespace
            {
                typedef Expected RDB;

                static inline
                void GrammarVisit(RDB        & rdb,
                                  const Rule & rule)
                {
                    if( !rdb.write(rule) ) return; // visited
                    switch(rule.uuid)
                    {
                        case Terminal::UUID:
                            break; // nothing else to do

                        case Option::UUID:
                        case Repeat::UUID:
                            GrammarVisit(rdb, dynamic_cast<const Wildcard &>(rule).rule );
                            break;

                        case Alternate::UUID:
                        case Aggregate::UUID:
                            if(dynamic_cast<const Compound &>(rule)->size<=0)
                                throw Specific::Exception(rule.name->c_str(), "empty compound!!");
                            for(const RNode *node=dynamic_cast<const Compound &>(rule)->head;node;node=node->next)
                                GrammarVisit(rdb,**node);
                            break;

                        default:
                            throw Specific::Exception(rule.name->c_str(), "unknown uuid='%s'", FourCC(rule.uuid).c_str());
                    }
                }
            }

            void Grammar:: validate()
            {
                if(rules.size<=0)
                    throw Specific::Exception(lang->c_str(), "empty grammar");

                {
                    const RDB  visited;
                    GrammarVisit(Coerce(visited),*rules.head);

                    {
                        String missing;
                        for(const Rule *rule=rules.head;rule;rule=rule->next)
                        {
                            if(!visited.query(*rule)) missing += ' ' + *rule->name;
                        }
                        if(missing.size())
                            throw Specific::Exception(lang->c_str(), "orphaned '%s'", missing.c_str());
                    }

                    {
                        String unknown;
                        for(RDB::ConstIterator it=visited.begin();it!=visited.end();++it)
                        {
                            const Rule &rule = **it;
                            if(!rules.owns(&rule)) unknown += ' ' + *rule.name;
                        }
                        if(unknown.size())
                            throw Specific::Exception(lang->c_str(), "unknown '%s'", unknown.c_str());
                    }
                }

                freeze();
            }
        }

    }

}

