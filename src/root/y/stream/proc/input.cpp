

#include "y/stream/proc/input.hpp"
#include "y/exception.hpp"
#include "y/ability/lockable.hpp"
#include <cstdio>

namespace Yttrium
{
    InputProcess:: ~InputProcess() noexcept
    {
    }


    const char * const InputProcess:: How      = "r";
    const char * const InputProcess:: CallSign = "InputProcess";


    static inline bool forceQuery(void * const handle,
                                  char &       data,
                                  const Identifier &title)
    {
        FILE * const fp = (FILE *)handle;
        Y_Giant_Lock();
        if(feof(fp)) return false;
        const size_t nr = fread(&data, 1, 1, fp);
        if(nr<=0) 
        {
            if(feof(fp)) return false;
            throw Specific::Exception(title->c_str(), "%s fread failure", InputProcess::CallSign);
        }
        return true;
    }

    bool InputProcess:: query(char &data)
    {
        assert(0!=handle);

        if(buffer.size>0)
        {
            data = buffer.pullHead();
            return true;
        }
        else
        {
            return forceQuery(handle,data,title);
        }
    }

    size_t InputProcess:: query(void * const addr, const size_t size)
    {
        assert( !(0==addr&&size>0) );
        char * p = (char *) addr;
        for(size_t i=0;i<size;++i)
        {
            char c = 0;
            if(!query(c)) return i;
            *(p++) = c;
        }
        return size;
    }


    void InputProcess:: store(const char C)
    {
        buffer >> C;
    }


}
