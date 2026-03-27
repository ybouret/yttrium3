//! \file

#ifndef Y_Memory_Archon_Included
#define Y_Memory_Archon_Included 1


#include "y/singleton.hpp"
#include "y/memory/page.hpp"
#include "y/core/meta-max.hpp"
#include "y/memory/metrics.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"
#include "y/ability/logging.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! LEVEL-2 Cache
        //
        //
        //______________________________________________________________________
        class Archon :
        public Singleton<Archon,ClassLockPolicy>,
        public Allocator,
        public Logging
        {
        public:
            static const char * const CallSign; //!< "Memory::Archon"
            static const Longevity    LifeTime      = LifeTimeFor::MemoryArchon;
            static const size_t       MinBlockBytes = MetaMax<sizeof(Page),2*sizeof(uint64_t)>::Value;
            static const unsigned     MinBlockShift = IntegerLog2<MinBlockBytes>::Value;
            static const size_t       MaxBlockBytes = Metrics::MaxPageBytes;
            static const unsigned     MaxBlockShift = Metrics::MaxPageShift;
            static const unsigned     NumSlots      = 1+MaxBlockShift - MinBlockShift;
            typedef ClassLockPolicy   Policy;
            class Code;

            virtual void * acquire(size_t & blockSize);
            virtual void   release(void * &blockAddr, size_t &blockSize) noexcept;
            virtual void   toXML(XML::Log &) const;

            //! acquire memory by its log2 size
            /**
             \param MinBlockShift <= blockShift << MaxBlockShift
             \return block[2^blockShift]
             */
            void * acquireBlock(const unsigned blockShift);

            //! release memory
            void   releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept;

            
        private:
            Y_Disable_Copy_And_Assign(Archon);
            friend class Singleton<Archon,ClassLockPolicy>;
            Archon();
            ~Archon() noexcept;
            Code * const code;

        };
    }
}

#endif // !Y_Memory_Archon_Included

