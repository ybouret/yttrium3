
#include "y/exception.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/copy.h"
#include "y/libc/str/cat.h"
#include "y/libc/str/cpy.h"
#include "y/libc/str/len.h"
#include "y/libc/str/fmt.h"
#include "y/core/max.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    const char * const Exception:: CallSign = "Exception";
    

    void Exception:: init() noexcept
    {
        Y_BZero(what_);
        Y_BZero(info_);
        Yttrium_Strcpy(what_,sizeof(what_),CallSign);
    }


    Exception:: ~Exception() noexcept
    {
        init();
    }

    Exception::Exception(const Exception &_) noexcept :
    info_()
    {
        Y_BCopy(what_,_);
        Y_BCopy(info_,_);
    }

    Exception:: Exception() noexcept :
    what_(),
    info_()
    {
        init();
    }

    Exception:: Exception(const char * const fmt,...) noexcept :
    what_(),
    info_()
    {
        init();
        
        assert(0!=fmt);
        va_list ap;
        va_start(ap,fmt);
        Yttrium_Strfmt(info_,sizeof(info_), fmt, &ap );
        va_end(ap);

    }

    const char * Exception:: what() const noexcept
    {
        return what_;
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
        static const char  sep      = '*';
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




    Exception & Exception:: cat(const char * const fmt, ...) noexcept
    {
        assert(0!=fmt);
        char temp[InfoLength];
        {
            va_list ap;
            va_start(ap,fmt);
            (void) Yttrium_Strfmt(temp,sizeof(temp), fmt, &ap );
            va_end(ap);
        }
        return *this << temp;
    }

    Exception & Exception:: pre(const char * const fmt, ...) noexcept
    {
        assert(0!=fmt);
        char temp[InfoLength];
        {
            va_list ap;
            va_start(ap,fmt);
            (void) Yttrium_Strfmt(temp,sizeof(temp), fmt, &ap );
            va_end(ap);
        }
        return *this >> temp;
    }



    Exception & Exception:: signedFor(const char * const varName, const char * const varPart) noexcept
    {
        if(varName)
        {
            cat(" for %s",varName);
            if(varPart)
            {
                cat(".%s",varPart);
            }
        }
        return *this;
    }


    namespace Specific
    {

        Exception:: Exception() noexcept :
        Yttrium::Exception()
        {

        }

        Exception:: Exception(const char * const nature,
                              const char * const fmt,
                              ...) noexcept :
        Yttrium::Exception()
        {
            Yttrium_Strcpy(what_,sizeof(what_),nature);
            va_list ap;
            va_start(ap,fmt);
            (void)Yttrium_Strfmt(info_,sizeof(info_), fmt, &ap );
            va_end(ap);
        }

        Exception:: ~Exception() noexcept
        {
        }

        Exception:: Exception(const Exception &_) noexcept : Yttrium::Exception(_)
        {
        }


    }

}
