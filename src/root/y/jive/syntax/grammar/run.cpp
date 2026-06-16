
#include "y/jive/syntax/grammar/core.hpp"
#include "y/exception.hpp"
#include "y/jive/lexer.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            namespace
            {
                static inline
                void rejectedWithNoCache(const Lexer           &lexer,
                                         const AutoPtr<Lexeme> &next)
                {
                    const char * const name = lexer.name->c_str();
                    if(next.isEmpty())
                    {
                        throw Specific::Exception(name,"rejected an empty stream");
                    }
                    else
                    {
                        Specific::Exception excp(name,"rejected before ");
                        next->addTo(excp,lexer.isMultiple(*next->name));
                        throw next->stamp(excp);
                    }
                }

                static inline
                void rejectedWithOnlyOne(const Lexer          &lexer,
                                         const AutoPtr<Lexeme> &next,
                                         const Lexeme          &last)
                {
                    const char * const  name = lexer.name->c_str();
                    Specific::Exception excp(name,"rejected after single ");
                    (void)last.stamp(last.addTo(excp,lexer.isMultiple(*last.name)));
                    if(next.isEmpty())
                    {
                        throw excp.cat(" and end of stream");
                    }
                    else
                    {
                        excp.cat(", followed by ");
                        throw next->addTo(excp, lexer.isMultiple(*next->name) );
                    }
                }
            }

            XNode * CoreGrammar:: run(Lexer &lexer, Source &source) const
            {
                assert(rules.size>0);
                Framework      framework(lexer,source);
                const Rule &   rule    = *rules.head;
                const Outcome  outcome = rule.accepts(framework);
                switch(outcome.result)
                {
                    case Accepted:
                        if(!framework.ok())
                            throw Specific::Exception(lang->c_str(),"'%s': empty AST", source->title->c_str());
                        return accepted( framework.yield(), lexer, source);

                    case Rejected:
                        break;
                }

                Lexemes         cache; lexer.sendCacheTo(cache);
                AutoPtr<Lexeme> next = lexer.pull(source);
                switch(cache.size)
                {
                    case 0: rejectedWithNoCache(lexer,next); break;
                    case 1: rejectedWithOnlyOne(lexer,next,*cache.tail); break;

                    default:
                        break;
                }
                Specific::Exception excp(lang->c_str(),"rejected ");
                assert(cache.size>=2);            assert(cache.tail);
                const Lexeme &last = *cache.tail; assert(last.prev);
                const Lexeme &prev = *last.prev;
                prev.addTo(excp, lexer.isMultiple(*prev.name) );
                last.stamp(excp).cat(" followed by ");
                last.addTo(excp, lexer.isMultiple(*last.name) );

                if( next.isEmpty() )
                {
                    throw excp.cat(" and end of stream");
                }
                else
                {
                    throw next->addTo(excp.cat(" and awaiting "), lexer.isMultiple(*next->name) );
                }

            }


            XNode * CoreGrammar:: accepted(XNode * const xnode,
                                           Lexer  &      lexer,
                                           Source &      source) const
            {
                //--------------------------------------------------------------
                //
                // secure node into tree
                //
                //--------------------------------------------------------------
                AutoPtr<XNode> tree(xnode);

                if(false)
                {
                    const String dotFile = *lang + "-raw-tree.dot";
                    Vizible::Render(dotFile,*tree,false);
                }

                //--------------------------------------------------------------
                //
                // check EOS
                //
                //--------------------------------------------------------------
                AutoPtr<Lexeme> curr = lexer.pull(source);
                if(curr.isValid())
                {
                    Specific::Exception excp(lang->c_str(),"extraneous ");
                    curr->addTo(excp,lexer.isMultiple(*curr->name));
                    {
                        const Lexeme * const last = tree->last();
                        if(last)
                        {
                            excp.cat(" after ");
                            last->addTo(excp,lexer.isMultiple(*last->name));
                        }
                    }
                    throw curr->stamp(excp);
                }

                //--------------------------------------------------------------
                //
                // ok, success!
                //
                //--------------------------------------------------------------
                return XNode::AST( tree.yield() );
            }



        }

    }

}

