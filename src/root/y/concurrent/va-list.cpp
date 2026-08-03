#include "y/concurrent/va-list.hpp"
#include "y/format/hexadecimal.hpp"

#include <cstring>


namespace Yttrium
{
    namespace  Concurrent
    {
        VaList:: VaList() noexcept :
        wptr(0),
        rptr(0),
        data(0),
        wksp()
        {
            Coerce(data) = static_cast<uint8_t *>( memset(wksp,0,sizeof(wksp)) );
            wptr         = data;
            rptr         = data;
        }

        VaList:: ~VaList() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const VaList &vp)
        {
            return Hexadecimal::Display(os,vp.data,vp.usedBytes());
        }


        size_t VaList:: usedBytes() const noexcept
        {
            return static_cast<size_t>(wptr-data);
        }

        size_t VaList:: freeBytes() const noexcept
        {
            assert(wptr>=data);
            assert(wptr<=data+RequiredBytes);
            return static_cast<size_t>( (data+RequiredBytes)-wptr );
        }

        size_t VaList:: codeBytes() const noexcept
        {
            assert(wptr>=data);
            assert(wptr<=data+RequiredBytes);
            assert(rptr>=data);
            assert(rptr<=wptr);
            return static_cast<size_t>(wptr-rptr);
        }

        void * VaList:: unpack() noexcept
        {
            assert(codeBytes()>=sizeof(void*));
            void * const addr = *(void **)rptr;
            rptr += sizeof(void*);
            return addr;
        }

        VaList & VaList:: record(const void * const addr) noexcept
        {
            assert( freeBytes() >= sizeof(void *) );
            *(void **)wptr = (void *) addr;
            wptr += sizeof(void *);
            return *this;
        }

        VaList & VaList:: mwrite(const void * const addr) noexcept
        {
            assert( freeBytes() >= MethodLength );
            (void)memcpy(wptr,addr,sizeof(Meth));
            wptr += MethodLength;
            return *this;
        }


        void VaList:: mquery(void * const addr) noexcept
        {
            assert(codeBytes()>=MethodLength);
            memcpy(addr,rptr,sizeof(Meth));
            rptr += MethodLength;
        }


    }
}
