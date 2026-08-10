#include "y/concurrent/subdivisions.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace
        {
            typedef Memory::Archon MemMgr;

        }

        Subdivisions:: Subdivisions(const size_t n) :
        ncpu(n),
        shmm()
        {
            assert(ncpu>0);
        }

        Subdivisions:: Subdivisions(const size_t n, const LocalMemory &localMem) noexcept :
        ncpu(n),
        shmm(localMem)
        {
            assert(ncpu>0);
        }

        Subdivisions:: Subdivisions(const Subdivisions &parent) noexcept :
        ncpu(parent.ncpu),
        shmm(parent.shmm)
        {

        }


        Subdivisions:: ~Subdivisions() noexcept
        {
            
        }




        Subdivision & Subdivisions:: sub(const size_t i) noexcept
        {
            const Subdivisions &self = *this;
            return Coerce(self.sub(i));
        }


        void Subdivisions:: updateLocalCaches() noexcept
        {
            for(size_t i=1;i<=ncpu;++i)
                sub(i).borrowFrom(*shmm);
        }


        void Subdivisions:: removeLocalCaches() noexcept
        {
            for(size_t i=1;i<=ncpu;++i)
            {
                sub(i).clearCache();
            }
        }

        void Subdivisions:: ensureLocalCaches(const size_t bytes)
        {
            if(bytes>0)
            {
                shmm->ensure(bytes,ncpu);
                updateLocalCaches();
            }

#if !defined(NDEBUG)
            for(size_t i=1;i<=ncpu;++i)
            {
                assert( sub(i).bytes >= bytes );
            }
#endif // !defined(NDEBUG)
        }

        
    }

}
