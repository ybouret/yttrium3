
#include "y/string/format.hpp"
#include "y/libc/str/fmt.h"
#include "y/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include <cstdarg>
#include <cerrno>

namespace Yttrium
{
    

    String Formatted::Get(const char * const fmt,...)
    {
        assert(fmt!=0);
        size_t length = 0;
        int    result = 0;
        {
            Y_Giant_Lock();
            va_list ap;
            va_start(ap,fmt);
            result = Yttrium_Strfmt(0,0,fmt, &ap);
            va_end(ap);
            if(result<0)
                throw Libc::Exception(errno,"vsnprint(...) level-1");
            length = size_t( result );
        }

        String str(WithAtLeast,length,InitBlankString); assert(str.size()==length);

        {
            va_list ap;
            va_start(ap,fmt);
            Y_Giant_Lock();
            const int result2 = Yttrium_Strfmt(str(),length+1,fmt, &ap);
            if(result2!=result)
                throw Libc::Exception(errno,"vsnprint(...) level-2");
            va_end(ap);
        }

        return str;

    }

}
