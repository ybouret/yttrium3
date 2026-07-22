#define _CRT_SECURE_NO_WARNINGS

#include "y/rtld/spyndle/api.hpp"
#include <cstring>
#include <cassert>

namespace Yttrium
{

    char SpyndleAPI:: What[] = { 0 };
    char SpyndleAPI:: Info[] = { 0 };

    void SpyndleAPI:: NoMessage() noexcept
    {
        memset(What,0,sizeof(What));
        memset(Info,0,sizeof(Info));
    }

    void SpyndleAPI:: OnError(const char * const what, const char * const when) noexcept
    {
        assert(what);
        assert(when);
        strncpy(What,what,sizeof(What)-1);
        strncpy(Info,when,sizeof(Info)-1);
    }

    void SpyndleAPI:: OnError(const std::exception &excp, const char * const when) noexcept
    {
        assert(when);
        assert(excp.what());
        strncpy(What,excp.what(),sizeof(What)-1);
        strncpy(Info,when,       sizeof(Info)-1);
    }

    void SpyndleAPI:: OnError(const Exception &excp) noexcept
    {
        assert(excp.what());
        assert(excp.info());
        strncpy(What,excp.what(),sizeof(What)-1);
        strncpy(Info,excp.info(),sizeof(Info)-1);
    }

    SpyndleAPI:: SpyndleAPI() noexcept {}

    SpyndleAPI:: ~SpyndleAPI() noexcept {}


}

