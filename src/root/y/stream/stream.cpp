
#include "y/stream/stream.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    Stream:: ~Stream() noexcept
    {
    }

    Stream:: Stream() : title()
    {
    }


    const char * Stream:: callSign() const noexcept
    {
        return title.c_str();
    }

    Exception & Stream:: stamp(Exception &excp)
    {
        return excp.pre("%s:", callSign());
    }



}


