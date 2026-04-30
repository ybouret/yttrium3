
#include "y/jive/module.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Module:: ~Module() noexcept
        {
        }

        Module:: Module(const Input &in) noexcept :
        Object(),
        Spot(in->title),
        input(in)
        {
        }

        Char * Module:: get()
        {
            char c = 0;
            if( input->query(c) )
            {
                Char * const ch = new Char(*this,(uint8_t)c);
                ++Coerce(column);
                return ch;
            }
            else
                return 0;
        }

        void Module:: newLine() noexcept
        {
            ++Coerce(line);
            Coerce(column) = 1;
        }


    }

}

#include "y/stream/libc/input.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Module * Module:: OpenFile(const String &fileName)
        {
            const Input in( new InputFile(fileName) );
            return new Module(in);
        }

        Module * Module:: OpenFile(const char * const fileName)
        {
            const Input in( new InputFile(fileName) );
            return new Module(in);
        }

        Module * Module:: OpenStdIn()
        {
            const Input in( new InputFile(StdIn) );
            return new Module(in);
        }

    }

}

