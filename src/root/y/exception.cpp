
#include "y/exception.hpp"
#include "y/libc/bzero.h"
#include "y/libc/bcopy.h"
#include "y/libc/strcat.h"
#include "y/libc/strcpy.h"
#include "y/libc/strlen.h"
#include "y/core/max.hpp"
#include <iostream>

namespace Yttrium
{
    const char * const Exception:: CallSign = "Exception";
    


    Exception:: ~Exception() noexcept
    {
        Y_BZero(info_);
    }

    Exception::Exception(const Exception &_) noexcept :
    info_()
    {
        Y_BCopy(info_,_);
    }

    Exception:: Exception() noexcept :
    info_()
    {
        Y_BZero(info_);
    }

    const char * Exception:: what() const noexcept
    {
        return CallSign;
    }

    const char * Exception:: info() const noexcept
    {
        return info_;
    }



    Exception & Exception:: operator<<(const char * const text) noexcept
    {
        Yttrium_Strcat(info_,sizeof(info_),text);
        return *this;
    }

    Exception & Exception:: operator>>(const char * const text) noexcept
    {
        char temp[InfoLength];
        Y_BZero(temp);
        Yttrium_Strcpy(temp, sizeof(temp), text);
        Yttrium_Strcat(temp, sizeof(temp), info_);
        Yttrium_BCopy(info_, temp, InfoLength);
        return *this;
    }

    static inline std::ostream & printLine(std::ostream &os, size_t size, const char sep)
    {
        while(size-- > 0) os << sep;
        return os;
    }

    void Exception:: display(std::ostream &os) const
    {
        static const char  sep = '*';
        const char * const whatText = what();
        const char * const infoText = info();
        const size_t       whatSize = Yttrium_Strlen(whatText);
        const size_t       infoSize = Yttrium_Strlen(infoText);
        const size_t       width    = Max(whatSize,infoSize);
        const size_t       frame    = width + 4;
        const size_t       padding  = width + 1;
        printLine(os,frame,sep) << std::endl;
        printLine( os << sep << ' ' << whatText,padding-whatSize,' ') << sep << std::endl;
        printLine( os << sep << ' ' << infoText,padding-infoSize,' ') << sep << std::endl;
        printLine(os,frame,sep) << std::endl;
    }

    namespace Specific
    {
        Exception:: ~Exception() noexcept
        {
            Y_BZero(what_);
        }

        Exception:: Exception(const Exception &_) noexcept : Yttrium::Exception(_)
        {
            Y_BCopy(what_,_);
        }

        const char * Exception:: what() const noexcept
        {
            return what_;
        }
    }

}
