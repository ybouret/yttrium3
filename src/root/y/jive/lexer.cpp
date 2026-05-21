
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

    }

}


