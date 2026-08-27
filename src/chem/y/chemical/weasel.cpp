#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/formula/translator.hpp"
#include "y/chemical/reactive/equilibrium/translator.hpp"
#include "y/type/pulverize.hpp"
#include "y/lua++/state.hpp"

#include "y/graphviz/color-scheme.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Weasel:: CallSign = "Weasel";
        static const char * const LawColorSchemeName = "accent8";


        class Weasel::Code
        {
        public:
            inline explicit Code() :
            lvm( new Lua::State() ),
            parser(),
            ftrans(parser.formula.name),
            etrans(parser.equilibrium.name,lvm),
            scs( GraphViz::ColorScheme::Query(Species::ColorSchemeName) ),
            ecs( GraphViz::ColorScheme::Query(Equilibrium::ColorSchemeName) ),
            lcs( GraphViz::ColorScheme::Query(LawColorSchemeName) )
            {
            }


            inline virtual ~Code() noexcept
            {
            }

            Lua::VM                 lvm;
            Parser                  parser;
            Formula::Translator     ftrans;
            Equilibrium::Translator etrans;

            const GraphViz::ColorScheme  &scs;
            const GraphViz::ColorScheme  &ecs;
            const GraphViz::ColorScheme  &lcs;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            static void * WeaselCode[ Alignment::WordsFor<Weasel::Code>::Count ];
        }

        Weasel:: Weasel() :
        code( new( Y_BZero(WeaselCode) ) Code() ),
        lang(code->parser.lang),
        formula(code->ftrans.lang),
        equilibrium(code->etrans.lang),
        alias(code->parser.alias.name),
        formulaTranslator(code->ftrans)
        {
            std::cerr << "sizeof(WeaselCode) = " << sizeof(WeaselCode) << std::endl;
        }

        Weasel:: ~Weasel() noexcept
        {
            assert(code);
            Pulverize(code);
        }

        XNode * Weasel:: parse(Jive::Module * const m)
        {
            assert(code);
            return code->parser.getAST(m);
        }

        void Weasel:: operator()(Jive::Module * const m,
                                 Library    &lib,
                                 Equilibria &eqs)
        {
            AutoPtr<XNode> tree = parse(m);
            assert( tree.isValid() );
            assert(*lang == *tree->rule.name);
            if(false)
            {
                const String dotFile = *lang + "-ast-tree.dot";
                Vizible::Render(dotFile,*tree,false);
            }
            XList &top = tree->list();
            while(top.size)
            {
                AutoPtr<XNode> node = top.popHead();
                const String & name = *node->rule.name;

                std::cerr << "-- processing '" << name << "'" << std::endl;
                if(name==*formula)
                {
                    const Formula f( node.yield() );
                    (void) lib[f];
                    continue;
                }

                if(name==*equilibrium)
                {
                    code->etrans(node,lib,eqs);
                    continue;
                }

                if(name==*alias)
                {
                    const String expr = node->lexeme().raw(1);
                    onAlias(expr,lib,eqs);
                }

                
            }

        }

        //xreal_t Weasel:: eval(const String &expr)
        //{
        //    assert(code);
        //    return code->lvm->eval<lua_Number>(expr);
        //}

        String Weasel:: getColorFor(const Species &sp, const Level L) const noexcept
        {
            assert(code);
            return code->scs[ sp.indx[L] ];
        }

        String Weasel:: getColorFor(const Components &eq, const Level L) const noexcept
        {
            assert(code);
            return code->ecs[ eq.indx[L] ];
        }

        String Weasel::  getColorFor(const size_t lawIndx) const noexcept
        {
            assert(code);
            return code->lcs[ lawIndx ];
        }


    }

}

