#include "y/jive/lexical/scanner/code.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Unit * Scanner:: get(Source &source, Command &command)
            {
                assert(code);
                command.reset();
                const Char * const     peek = source.peek(); if(!peek) return 0;
                const uint8_t          byte = **peek;
                const MetaList * const prml = code->table.query(byte); // pointer to rules meta list
                if(!prml)
                {
                    Specific::Exception excp(name->c_str(),"invalid char '%s'", ASCII::Printable::Char[byte]);
                    throw peek->stamp(excp);
                }
                return 0;
            }

        }

    }

}

