#include "y/jive/lexical/scanner.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(jive_scanner)
{
    Lexical::Scanner scan("MyScanner");

    Y_SIZEOF( CxxListOf<Lexical::Rule> );
    Y_SIZEOF( Core::ListOf<Lexical::Rule> );

    {
        const Identifier name = "INT";
        const Motif      form = RegExp::Compile("[:digit:]+",0);
        scan.add(new Lexical::Rule(name,form,Lexical::Rule::Emit,name) );
    }

    {
        const Identifier name = "DBL";
        const Motif      form = RegExp::Compile("[:digit:]+([.][:digit:]+)?",0);
        scan.add(new Lexical::Rule(name,form,Lexical::Rule::Emit,name) );
    }


    {
        const Identifier name = "ID";
        const Motif      form = RegExp::Compile("[:alpha:][:word:]*",0);
        scan.add(new Lexical::Rule(name,form,Lexical::Rule::Emit,name) );
    }

    {
        const Identifier name = "BLANK";
        const Motif      form = RegExp::Compile("[:blank:]",0);
        scan.add(new Lexical::Rule(name,form,Lexical::Rule::Drop,name) );
    }

    {
        const Identifier name = "ENDL";
        const Motif      form = RegExp::Compile("[:endl:]",0);
        scan.add(new Lexical::Rule(name,form,Lexical::Rule::Drop|Lexical::Rule::Endl,name) );
    }



    if(argc>1)
    {
        Source           source( Module::OpenFile(argv[1]) );
        Lexical::Command cmd;
        Lexemes          lxm;
        while(true)
        {
            Lexeme * const lx = scan.get(source,cmd);
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

