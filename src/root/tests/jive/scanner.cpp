#include "y/jive/lexical/scanner.hpp"
#include "y/type/conversion.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(jive_scanner)
{

    Y_CHECK( Y_Is_SuperSubClass_Strict(Counted,Lexical::Action) );
    Y_CHECK( Y_Is_SuperSubClass_Strict(Object,Lexical::Action)  );

    Lexical::Scanner scan("MyScanner");

    scan.emit("INT","[:digit:]+");
    scan.emit("DBL","[:digit:]+([.][:digit:]+)?");
    scan.emit("ID","[:alpha:][:word:]*");
    scan.drop("BLANK","[:blank:]");
    scan.endl("ENDL","[:endl:]");




    if(argc>1)
    {
        Source           source( Module::OpenFile(argv[1]) );
        Lexical::Command cmd;
        Lexemes          lxm;
        while(true)
        {
            Lexeme * const lx = scan.probe(source,cmd);
            if(!lx) break;
            lxm.pushTail(lx);
        }

        for(const Lexeme *lx = lxm.head;lx;lx=lx->next)
        {
            std::cerr << lx->title << ":" << lx->line << ":" << lx->column << ": '" << lx->name << "' " << *lx << std::endl;
        }

    }


}
Y_UDONE()

