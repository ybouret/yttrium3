
#include "y/exception.hpp"
#include "y/libc/bzero.h"
#include "y/libc/bcopy.h"
#include "y/libc/strcat.h"
#include "y/libc/strcpy.h"

namespace Yttrium
{
    const char * const Exception:: CallSign = "Exception";
    
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


    Exception & Exception:: operator<<(const char * const text) noexcept
    {
        Yttrium_Strcat(what_,sizeof(what_),text);
        return *this;
    }

    Exception & Exception:: operator>>(const char * const text) noexcept
    {
        char temp[WhatLength];
        Y_BZero(temp);
        Yttrium_Strcpy(temp, sizeof(temp), text);
        Yttrium_Strcat(temp, sizeof(temp), what_);
        Yttrium_BCopy(what_, temp, WhatLength);
        return *this;
    }



}
