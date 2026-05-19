
#include "y/jive/regexp.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/dictionary.hpp"

using namespace Yttrium;


Y_UTEST(jive_rx)
{

    Jive::Dictionary dict;

    dict("INT","[0-9]+");
    Vizible::Render("int.dot", dict["INT"]);


    if(argc>1)
    {
        AutoPtr<Jive::Pattern> p = Jive::RegExp::Compile(argv[1],&dict);
        
        {
            Vizible::Render("rx.dot",*p);
        }
    }


}
Y_UDONE()
