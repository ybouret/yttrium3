#include "y/concurrent/subdivisions.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        Subdivisions:: Subdivisions(const size_t n) noexcept :
        ncpu(n),
        wlen(0),
        wksp(0)
        {
            assert(ncpu>0);
        }

        Subdivisions:: ~Subdivisions() noexcept
        {
            
        }

        namespace
        {
            typedef Memory::Archon MemMgr;

        }

        void Subdivisions:: deleteCache() noexcept
        {
            if(wlen)
            {
                static Memory::Allocator & mgr = MemMgr::Location();
                mgr.release( Coerce(wksp), Coerce(wlen) );
                updateCache();
            }
            else
            {
                assert(0==wksp);
            }
        }

        Subdivision & Subdivisions:: sub(const size_t i) noexcept
        {
            const Subdivisions &self = *this;
            return Coerce(self.sub(i));
        }

        void Subdivisions:: updateCache() noexcept
        {
            const size_t bps = wlen / ncpu;
            char *       ptr = static_cast<char *>(wksp);
            for(size_t i=1;i<=ncpu;++i,ptr+=bps)
            {
                Subdivision &s =  sub(i);
                Coerce(s.entry) = ptr;
                Coerce(s.bytes) = bps;
            }
        }

        void Subdivisions:: ensureCache(const size_t bytesPerSubdivision)
        {
            const size_t bps = Alignment::SystemMemory::Ceil(bytesPerSubdivision);
            size_t       num = ncpu * bps;
            if(num>wlen)
            {
                static Memory::Allocator &mgr = MemMgr::Instance();
                void * ptr = mgr.acquire(num);
                CoerceSwap(ptr,wksp);
                CoerceSwap(num,wlen);
                if(num>0) { assert(ptr); mgr.release(ptr,num); }
                updateCache();
            }
        }


    }

}
