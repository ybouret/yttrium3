
#include "y/jive/syntax/grammar/core.hpp"
#include "y/exception.hpp"
#include "y/jive/lexer.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

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

                std::cerr << "Rejected!" << std::endl;

                std::cerr << "Blocked : " << (outcome.status == Blocked) << std::endl;

                Lexemes         cache; lexer.sendCacheTo(cache);
                AutoPtr<Lexeme> next = lexer.pull(source);
                std::cerr << "next=" << next << std::endl;

                if( next.isEmpty() )
                {
                    // EOS while running : interrupted something ?
                    if(cache.size)
                    {
                        // may be syntax error or not
                        Specific::Exception excp(lang->c_str(),"end of stream after ");
                        const Lexeme       &last = *cache.tail;
                        last.addTo(excp,lexer.isMultiple(*last.name));
                        throw last.stamp(excp);
                    }
                    else
                    {
                        throw Specific::Exception(lang->c_str(),"rejected empty stream");
                    }
                }
                else
                {

                }


                return 0;
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
                AutoPtr<XNode> tree(xnode); Vizible::Render("tree.dot",*tree,true);

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
                return tree.yield();
            }


            
        }

    }

}

