

#include "y/jive/syntax/rule/wildcard/repeat.hpp"
#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"
#include "y/jive/syntax/xnode.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Repeat:: ~Repeat() noexcept
            {
            }

            namespace
            {
                static inline
                String * NameRepeat(const Rule &source, const size_t nmin)
                {
                    static const char zom = '*';
                    static const char oom = '*';

                    const char * const text = source.name->c_str();
                    const size_t       tlen = source.name->size();

                    switch(nmin)
                    {
                        case 0: return new String(text,tlen,&zom,1);
                        case 1: return new String(text,tlen,&oom,1);
                        default:
                            break;
                    }
                    assert(nmin>=2);

                    String rhs = ">="; rhs += Decimal(nmin).c_str();
                    return new String(text,tlen,rhs.c_str(),rhs.size());
                }
            }

            Repeat:: Repeat(const Rule &source, const size_t nmin) :
            Wildcard(NameRepeat(source,nmin),UUID,source),
            atLeast(nmin)
            {
            }

            OutputStream & Repeat:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=hexagon";
                return Endl(fp<< ']');
            }


            Y_Jive_Syntax_Rule_Impl(Repeat)
            {
                //--------------------------------------------------------------
                //
                //
                // initialize
                //
                //
                //--------------------------------------------------------------
                const Nesting  nesting(framework);
                Framework      workspace(Replicate,framework);
                Outcome        outcome(Accepted,Healthy,Running);
                XList &        xlist = workspace.set( XNode::Create(*this) )->list();

                //--------------------------------------------------------------
                //
                //
                // loop
                //
                //
                //--------------------------------------------------------------
                while(true)
                {
                    const Outcome rout = rule.accepts(workspace);
                    if(rout.status==Blocked)  outcome.status = Blocked;
                    if(rout.result==Rejected) break;
                    if(rout.sanity==Fragile)  throw Specific::Exception(rule.name->c_str(),"infinite repeat detected!");
                }

                //--------------------------------------------------------------
                //
                //
                // study result
                //
                //
                //--------------------------------------------------------------
                if(xlist.size<atLeast)
                {
                    //----------------------------------------------------------
                    //
                    // rejected
                    //
                    //----------------------------------------------------------
                    workspace.dump();
                    outcome.result = Rejected;
                    return outcome;
                }

                if(xlist.size>0)
                {
                    //----------------------------------------------------------
                    //
                    // healthy
                    //
                    //----------------------------------------------------------
                    framework.join(workspace);
                    return outcome;
                }
                else
                {
                    //----------------------------------------------------------
                    //
                    // fragile !
                    //
                    //----------------------------------------------------------
                    assert(0==atLeast);
                    outcome.sanity = Fragile;
                    return outcome;
                }


            }
        }

    }

}
