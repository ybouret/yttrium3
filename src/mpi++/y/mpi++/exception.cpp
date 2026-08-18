#include "y/mpi++/api.hpp"
#include "y/libc/str/fmt.h"
#include <cstring>
#include "y/system/error.hpp"

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
            std::cerr << "info_:'" << info_ << "'" << std::endl;
            va_end(ap);
        }


        int resultLen = sizeof(what_);
        (void) MPI_Error_string(err,what_, &resultLen);

        std::cerr << "MPI:Excp:info: " << info_ << std::endl;
        std::cerr << "MPI:Excp:what: " << what_ << std::endl;
        std::cerr << std::endl;

    }



}

