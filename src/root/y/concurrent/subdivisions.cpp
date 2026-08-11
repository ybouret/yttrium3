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
        Splitting::Scheme(n)
        {
            assert(parallelism>0);
        }



        Subdivisions:: Subdivisions(const Splitting::Scheme &scheme) noexcept :
        Splitting::Scheme(scheme)
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
            for(size_t i=1;i<=parallelism;++i)
                sub(i).borrowFrom(*localMemory);
        }


        void Subdivisions:: removeLocalCaches() noexcept
        {
            for(size_t i=1;i<=parallelism;++i)
            {
                sub(i).clearCache();
            }
        }

        void Subdivisions:: ensureLocalCaches(const size_t bytes)
        {
            if(bytes>0)
            {
                localMemory->ensure(bytes,parallelism);
                updateLocalCaches();
            }

#if !defined(NDEBUG)
            for(size_t i=1;i<=parallelism;++i)
            {
                assert( sub(i).bytes >= bytes );
            }
#endif // !defined(NDEBUG)
        }

        
    }

}
