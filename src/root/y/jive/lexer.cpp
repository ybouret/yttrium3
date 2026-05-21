
#include "y/jive/lexer.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Lexer:: ~Lexer() noexcept
        {
            psdb.release();
            (void)liberate();
        }

        void Lexer:: initialize()
        {
            const PScanner self(this);
            withhold();
            try
            {
                if(!psdb.insert(self))
                    throw Specific::Exception(name->c_str(),"failed to initialized database!!");
            }
            catch(...)
            {
                (void) liberate();
                throw;
            }
        }

        Lexical::Scanner & Lexer:: record(const PScanner &ps)
        {
            if(!psdb.insert(ps))
                throw Specific::Exception(name->c_str(),"multiple extension '%s", ps->name->c_str());
            return Coerce(*ps);
        }

        void Lexer:: unget(Lexeme * const lx) noexcept
        {
            assert(lx);
            lexemes.pushHead(lx);
        }

        Lexeme * Lexer:: get(Source &source)
        {
            if(lexemes.size)
            {
                return lexemes.popHead();
            }
            else
            {
                return 0;
            }

        }



    }

}


