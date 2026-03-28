#include "y/system/error.hpp"
#include "y/libc/str/cpy.h"
#include "y/libc/str/trim.h"
#include "y/config/setup.hpp"
#include <cassert>
#include <cstring>

#if defined(_MSC_VER)
#  pragma warning ( disable : 4996 )
#endif

namespace Yttrium
{
    namespace Libc
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type   errorCode) noexcept
        {
            assert(NULL!=errorBuffer);
            assert(errorLength>0);
            return Yttrium_Strcpy(errorBuffer, errorLength, strerror(errorCode));
        }
    }
}

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace Yttrium
{
    namespace Windows
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type   errorCode) noexcept
        {
            assert(NULL!=errorBuffer);
            assert(errorLength>0);
            ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                            0,
                            errorCode,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            errorBuffer,
                            DWORD(errorLength),
                            0);
            return Yttrium_Strtrim(errorBuffer);
        }
    }
}
#else
namespace Yttrium
{
    namespace Windows
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type ) noexcept
        {
            assert(NULL!=errorBuffer);
            assert(errorLength>0);
            return Yttrium_Strcpy(errorBuffer, errorLength, Core::Unknown);
        }
    }

}
#endif

#if defined(Y_Darwin)
extern "C"
{
    const char * Yttrium_mach_error_string(const int);
};

namespace Yttrium
{
    namespace Mach
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type   errorCode) noexcept
        {
            assert(NULL!=errorBuffer);
            assert(errorLength>0);
            return Yttrium_Strcpy(errorBuffer, errorLength, Yttrium_mach_error_string(errorCode));
        }
    }
}
#endif // defined(Y_Darwin)


#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

namespace Yttrium
{
    template <typename ERROR_API> static inline
    void OnCritical(const typename  ERROR_API::Type err,
                    const char * const              fmt,
                    va_list &                       ap) noexcept
    {

        static const char Prolog[] = "\t*** ";
        try
        {
            (std::cerr << std::endl << Prolog).flush();
            char buffer[256];
            ERROR_API::Format(buffer,sizeof(buffer),err);
            if(0!=stderr)
            {
                vfprintf(stderr,fmt,ap);
                fflush(stderr);
            }
            std::cerr << std::endl << Prolog << "Critical Error: " << buffer << std::endl << std::endl;
        }
        catch(...)
        {
        }
        abort();
    }

#if defined(_MSC_VER)
    // unreachable va_end(ap)
#pragma warning ( disable : 4702 )
#endif

    namespace Libc
    {
        void Error::Critical(const Type errorCode, const char * const fmt,...) noexcept
        {
            assert(0!=fmt);
            va_list ap;
            va_start(ap,fmt);
            OnCritical<Error>(errorCode,fmt,ap);
            va_end(ap);
        }
    }


    namespace Windows
    {
        void Error::Critical(const Type errorCode,  const char * const fmt,...) noexcept
        {
            assert(0!=fmt);
            va_list ap;
            va_start(ap,fmt);
            OnCritical<Error>(errorCode,fmt,ap);
            va_end(ap);
        }
    }

#if defined(Y_Darwin)
    namespace Mach
    {

        void Error:: Critical(const Type errorCode,  const char * const fmt,...) noexcept
        {
            assert(0!=fmt);
            va_list ap;
            va_start(ap,fmt);
            OnCritical<Error>(errorCode,fmt,ap);
            va_end(ap);
        }
    }

#endif

}


