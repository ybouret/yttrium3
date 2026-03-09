
#include "y/exception.hpp"
#include <cstring>

namespace Yttrium
{
    void Exception:: ldz() noexcept
    {
        memset(what_,0,sizeof(what_));
    }

    Exception:: ~Exception() noexcept
    {
        ldz();
    }

    Exception:: Exception() noexcept :
    what_()
    {
        ldz();
    }

    const char * Exception:: what() const noexcept
    {
        return what_;
    }

}
