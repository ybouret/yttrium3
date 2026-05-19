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
        scan.add(new Lexical::Rule(name,form,0x00,name) );
    }

    {
        const Identifier name = "DBL";
        const Motif      form = RegExp::Compile("[:digit:]+([.][:digit:]+)?",0);
        scan.add(new Lexical::Rule(name,form,0x00,name) );
    }



}
Y_UDONE()

