#include "y/chemical/reactive/equilibrium/translator.hpp"
#include "y/chemical/reactive/equilibrium/constant.hpp"
#include "y/jive/syntax/rule.hpp"
#include "y/ascii/convert.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/lua++/function.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Equilibrium:: Translator:: Translator(const Identifier &id,
                                              const Lua::VM    &vm) :
        lang(id),
        lvm(vm)
        {
        }

        Equilibrium:: Translator:: ~Translator() noexcept
        {
        }

        namespace
        {
            static inline bool isBlank(const char c) noexcept
            {
                switch(c)
                {
                    case ' ':
                    case '\t':
                        return true;

                    default:
                        break;
                }
                return false;
            }
        }

        namespace
        {
            class LuaEquilibrium : public Equilibrium
            {
            public:
                inline explicit
                LuaEquilibrium(const String &eqName,
                               const size_t  eqIndx,
                               Lua::VM       &lvm,
                               const String  &kid) :
                Equilibrium(eqName,eqIndx),
                F(lvm,kid)
                {

                }

                inline virtual ~LuaEquilibrium() noexcept
                {
                }

            private:
                Y_Disable_Copy_And_Assign(LuaEquilibrium);
                Lua::Function<xreal_t> F;
                inline virtual xreal_t getK(const xreal_t t)
                {
                    const real_t tt  = (real_t)t;
                    return F(tt);
                }
            };
        }


        void Equilibrium:: Translator:: operator()(AutoPtr<XNode> & tree,
                                                   Library        & lib,
                                                   Equilibria     & eqs)
        {
            assert(tree.isValid());
            assert(tree->is(CallSign));
            Actor::List  xreac,xprod;
            const XList &xlist = tree->list(); assert(4==xlist.size);

            // extracting name
            XNode * xnode = xlist.head;

            assert(xnode->is("EID"));
            assert(xnode->lexeme().size>=2);

            const String       eqName = xnode->lexeme().str(1);
            const char * const eid    = eqName.c_str();

            // extracting reac
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("REAC"));
            fill(xreac,xnode,lib,eid);

            // extracting prod
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("PROD"));
            fill(xprod,xnode,lib,eid);

            //if(reac.size<=0 && prod.size<=0) throw Specific::Exception(CallSign, "empty '%s'",eid);

            // extracting KSTR
            xnode=xnode->next;
            assert(xnode);
            assert(xnode->is("KSTR"));
            const Jive::Token &ktkn = xnode->lexeme();
            String             kstr = ktkn.str();
            Algorithm::Crop(kstr,isBlank);

            if(kstr.size()<=0) throw Specific::Exception(CallSign, "'%s' has empty constant string",eid);

            Equilibrium * pEq    = 0;
            const char    kch    = kstr[1];
            const size_t  eqIndx =eqs->size()+1;

            if( isdigit(kch) ) {
                const xreal_t k  = lvm->eval<lua_Number>(kstr);
                pEq =  new ConstantEquilibrium(eqName,eqIndx,k);
                goto COMPILE;
            }

            if( isalpha(kch) ) {
                pEq = new LuaEquilibrium(eqName,eqIndx,lvm,kstr);
                goto COMPILE;
            }


            throw Specific::Exception(CallSign, "invalid constrant string '%s' for '%s'",kstr.c_str(),eid);

        COMPILE:
            {
                assert(pEq);

                // compiling equilibrium
                EqPtr eq(pEq);

                for(const Actor *ac=xreac.head;ac;ac=ac->next)
                    eq->addReac(ac->nu,ac->sp);


                for(const Actor *ac=xprod.head;ac;ac=ac->next)
                    eq->addProd(ac->nu,ac->sp);

                // adding to eqs
                eqs.add(eq);

                // freeze equilibrium
                eq->freeze();
            }

        }


        void Equilibrium:: Translator:: fill(Actor::List          & acl,
                                             XNode * const          xnode,
                                             Library              & lib,
                                             const char * const     eid)
        {
            assert(xnode);
            assert(xnode->is("REAC") || xnode->is("PROD") );
            assert(eid);

            XList       &xl = xnode->list();
            //std::cerr << "-- parsing " << ((xl.size + 1)>>1) << " " << xnode->name() << std::endl;

            for(XNode *sub=xl.head;sub;)
            {
                assert(sub->is("ACTOR"));

                XList &         al =  sub->list(); assert(1==al.size||2==al.size); assert(al.tail);
                const Formula   f(al.popTail());
                const Species & sp = lib[f];
                unsigned        nu = 1;

                if(al.head)
                {
                    assert(al.head->is("COEF"));
                    const String nuStr = al.head->lexeme().str();
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

