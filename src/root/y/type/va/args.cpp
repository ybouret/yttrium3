
#include "y/type/va/args.hpp"
#include "y/libc/block/zeroed.h"
#include <cstring>

namespace Yttrium
{
    VaArgs:: VaArgs(VaList &l) noexcept :
    list(l),
    rptr(l.data)
    {
    }

    VaArgs:: ~VaArgs() noexcept
    {
        
    }

    size_t VaArgs:: codeBytes() const noexcept
    {
        assert(rptr>=list.data);
        assert(rptr<=list.wptr);
        return static_cast<size_t>(list.wptr-rptr);
    }


    void * VaArgs:: unpack() noexcept
    {
        assert(codeBytes()>=sizeof(void*));
        void * const addr = *(void **)rptr; assert(0!=addr);
        rptr += sizeof(void*);
        return addr;
    }

    void VaArgs:: mquery(void * const addr) noexcept
    {
        assert(codeBytes()>=VaList::MethodLength);
        assert( Y_FALSE == Yttrium_Zeroed(rptr,sizeof(VaList::Meth)) );
        (void) memcpy(addr,rptr,sizeof(VaList::Meth));
        rptr += VaList::MethodLength;
    }

}
