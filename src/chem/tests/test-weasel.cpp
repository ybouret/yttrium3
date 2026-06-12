#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"
#include "y/jive/syntax/rule.hpp"
#include "y/chemical/formula/translator.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel &              weasel            = Weasel::Instance();
    Formula::Translator & formulaTranlator = weasel.formulaTranslator;
    formulaTranlator.verbose = true;


    if(argc>1)
    {
        AutoPtr<XNode> tree = weasel.parse( Jive::Module::OpenFile(argv[1]) );
        {
            const String dotFile = *weasel.lang + "-ast-tree.dot";
            Vizible::Render(dotFile,*tree,false);
        }

        // check top level
        Y_CHECK(*weasel.lang == *tree->rule.name);
        XList &top = tree->list();
        while(top.size)
        {
            AutoPtr<XNode> node = top.popHead();
            const String & name = *node->rule.name;
            std::cerr << "-- " << name << std::endl;
            if(name==*weasel.formula)
            {
                const Formula f( node.yield() );

                weasel.formulaTranslator(f->code);

                continue;
            }
        }

    }

}
Y_UDONE()

