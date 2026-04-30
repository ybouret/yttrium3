
#include "y/stream/memory/input.hpp"
#include "y/exception.hpp"
#include "y/core/min.hpp"
#include <cstring>

namespace Yttrium
{

    

    InputMemoryStream:: ~InputMemoryStream() noexcept
    {
    }


    bool InputMemoryStream:: query(char &c)
    {
        if(curr<last)
        {
            c = *(curr++);
            return true;
        }
        else
        {
            return false;
        }
    }

    void InputMemoryStream:: store(const char c)
    {
        if(curr<=base)  throw Specific::Exception(title->c_str(), "store without previous query");
        if(c!=curr[-1]) throw Specific::Exception(title->c_str(), "store invalid char");
        --curr;
    }

    size_t InputMemoryStream:: query(void * const buffer, const size_t buflen)
    {
        assert( !(0==buffer&&buflen>0) );
        const size_t numRead   = Min<size_t>(buflen,(size_t)(last-curr));
        memcpy(buffer,curr,numRead);
        curr += numRead;
        return numRead;
    }

}
