#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/formula/translator.hpp"
#include "y/type/pulverize.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Weasel:: CallSign = "Weasel";


        class Weasel::Code
        {
        public:
            inline explicit Code() :
            parser(),
            ftrans(parser.formula.name)
            {
            }


            inline virtual ~Code() noexcept
            {
            }

            Parser              parser;
            Formula::Translator ftrans;
            
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


    }

}

