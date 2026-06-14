#include "y/chemical/reactive/equilibrium/translator.hpp"
#include "y/jive/syntax/rule.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Equilibrium:: Translator:: Translator(const Identifier &id) :
        lang(id)
        {
        }

        Equilibrium:: Translator:: ~Translator() noexcept
        {
        }

        void Equilibrium:: Translator:: operator()(AutoPtr<XNode> &tree,
                                                   Library              &lib,
                                                   Equilibria           &eqs,
                                                   Formula::Translator  &ftr)
        {
            assert(tree.isValid());
            assert(tree->is(CallSign));
            reac.release();
            prod.release();
            const XList &xlist = tree->list(); assert(4==xlist.size);

            // extracting name
            XNode * xnode = xlist.head;

            assert(xnode->is("EID"));
            assert(xnode->lexeme().size>=2);

            const String       eqName = xnode->lexeme().str(1);
            const char * const eid    = eqName.c_str();
            std::cerr << "eqName='" << eqName << "'" << std::endl;

            // extracting reac
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("REAC"));
            fill(reac,xnode,lib,ftr,eid);

            // extracting prod
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("PROD"));
            fill(prod,xnode,lib,ftr,eid);

            // extracting KSTR
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("KSTR"));
            const Jive::Token &ktkn = xnode->lexeme();
            const String       kstr = ktkn.str();
            std::cerr << "KSTR=\"" << kstr << "\"" << std::endl;

            // compiling equilibrium
            


        }


        void Equilibrium:: Translator:: fill(Actor::List          & acl,
                                             XNode * const          xnode,
                                             Library              & lib,
                                             Formula::Translator  & ftr,
                                             const char * const     eid)
        {
            assert(xnode);
            assert(xnode->is("REAC") || xnode->is("PROD") );
            assert(eid);

            XList       &xl = xnode->list();
            std::cerr << "-- parsing " << ((xl.size + 1)>>1) << " " << xnode->name() << std::endl;

            for(XNode *sub=xl.head;sub;)
            {
                std::cerr << "\t" << sub->name() << std::endl;
                assert(sub->is("ACTOR"));

                XList &al =  sub->list(); assert(1==al.size||2==al.size);
                assert(al.tail);
                assert(al.tail->is(*ftr.lang));
                const Formula   f(al.popTail());
                const Species & sp = lib[f]; std::cerr << "using " << sp.name << std::endl;
                unsigned        nu = 1;
                if(al.head)
                {
                    assert(al.head->is("COEF"));
                    const String nuStr = al.head->lexeme().str();
                    std::cerr << "nu='" << nuStr << "'" << std::endl;
                    nu = ASCII::Convert::To<unsigned>(nuStr,sp.name.c_str(),"nu");
                    if(nu<=0) throw Specific::Exception(CallSign, "zero coefficient for '%s' in '%s'", sp.name.c_str(),eid);
                }

                acl.pushTail( new Actor(nu,sp,AsSpec) );


                // skipping '+' if present
                sub = sub->next;
                if(!sub) break;
                sub = sub->next;
                if(!sub) break;
            }

        }

    }

}

