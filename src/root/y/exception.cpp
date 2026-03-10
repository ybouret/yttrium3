
#include "y/exception.hpp"
#include "y/libc/bzero.h"
#include "y/libc/bcopy.h"

namespace Yttrium
{
    void Exception:: ldz() noexcept
    {
        Y_BZero(what_);
        Y_BZero(when_);
    }

    Exception:: ~Exception() noexcept
    {
        ldz();
    }

    Exception::Exception(const Exception &_) noexcept :
    when_(),
    what_()
    {
        Y_BCopy(when_,_);
        Y_BCopy(what_,_);
    }

    Exception:: Exception() noexcept :
    when_(),
    what_()
    {
        ldz();
    }

    const char * Exception:: what() const noexcept
    {
        return what_;
    }

    const char * Exception:: when() const noexcept
    {
        return when_;
    }


}
