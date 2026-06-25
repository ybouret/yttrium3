
#include "y/xml/log.hpp"
#include "y/core/indent.hpp"
#include <iostream>

namespace Yttrium
{
    namespace XML
    {
        Log:: Log(std::ostream &output,
                  bool &        verbosity) noexcept :
        os(output),
        verbose(verbosity),
        level(0)
        {

        }

        Log:: ~Log() noexcept
        {
        }

        std::ostream & Log:: Indent(std::ostream &out, const size_t n)
        {
            return Core::Indent(out,n<<2,' ');
        }

        std::ostream & Log:: operator()(void) noexcept
        {
            return Indent(os,level);
        }

        std::ostream & Log:: operator*() noexcept
        {
            return os;
        }

    }

}

