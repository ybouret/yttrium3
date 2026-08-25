
#include "y/stream/memory/output.hpp"


namespace Yttrium
{



    OutputMemoryStream:: ~OutputMemoryStream() noexcept
    {
    }
    

    void OutputMemoryStream:: flush() noexcept
    {
    }

    void OutputMemoryStream:: write(const char c)
    {
        data.pushTail(c);
    }

    void OutputMemoryStream:: write(const void * const entry, const size_t bytes)
    {
        const char * p = static_cast<const char *>(entry);
        for(size_t i=bytes;i>0;--i)
            write(*(p++));
    }

    Y_Proxy_Impl(OutputMemoryStream,data)

}

