#include "y/mpi++/api.hpp"
#include "y/libc/str/fmt.h"
#include <cstring>

namespace Yttrium
{

    MPI:: Exception:: ~Exception() noexcept
    {
    }

    MPI:: Exception:: Exception(const Exception &excp) noexcept :
    Yttrium::Exception(excp)
    {
        
    }


    MPI::Exception:: Exception(const int err, const char * fmt,...) noexcept :
    Yttrium::Exception()
    {

        assert(0!=fmt);
        {
            va_list ap;
            va_start(ap,fmt);
            Yttrium_Strfmt(info_,sizeof(info_), fmt, &ap );
            va_end(ap);
        }


        //memset(info,0,sizeof(info));
        int resultLen = sizeof(what_);
        (void) MPI_Error_string(err,what_, &resultLen);
        //{
        //    va_list ap;
        //    va_start(ap,fmt);
        //    (void) Core::Variadic::Format(tell, sizeof(tell), fmt, &ap);
        //    va_end(ap);
        //}
    }



}

