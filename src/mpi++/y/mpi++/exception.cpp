#include "y/mpi++/api.hpp"
#include "y/libc/str/fmt.h"
#include <cstring>
#include "y/system/error.hpp"
#include "y/core/min.hpp"

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
            (void) Yttrium_Strfmt(info_,sizeof(info_), fmt, &ap );
            va_end(ap);
        }

        {
            char output[MPI_MAX_ERROR_STRING];
            int  outlen=0;
            (void) MPI_Error_string(err,(char*) memset(output,0,sizeof(output)), &outlen);
            memset(what_,0,sizeof(what_));
            memcpy(what_,output,Min<size_t>(sizeof(what_)-1,(size_t)outlen));

        }
        
    }



}

