
#include "y/stream/stream.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    Stream:: ~Stream() noexcept
    {
    }

    

    const char * Stream:: callSign() const noexcept
    {
        return title->c_str();
    }

    Exception & Stream:: stamp(Exception &excp, const unsigned line)
    {
        return line ? excp.pre("%s:%u:", callSign(),line) : excp.pre("%s:", callSign());
    }



}


