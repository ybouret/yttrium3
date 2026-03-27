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
        /**
         uses Memory::Dyadic as LEVEL-1 cache
         */
        //
        //
        //______________________________________________________________________
        class Archon :
        public Singleton<Archon,ClassLockPolicy>,
        public Allocator,
        public Logging
        {
        public:
            static const char * const CallSign;                                                        //!< "Memory::Archon"
            static const Longevity    LifeTime      = LifeTimeFor::MemoryArchon;                       //!< life time
            static const size_t       MinBlockBytes = MetaMax<sizeof(Page),2*sizeof(uint64_t)>::Value; //!< alias
            static const unsigned     MinBlockShift = IntegerLog2<MinBlockBytes>::Value;               //!< alias
            static const size_t       MaxBlockBytes = Metrics::MaxPageBytes;                           //!< alias
            static const unsigned     MaxBlockShift = Metrics::MaxPageShift;                           //!< alias
            static const unsigned     NumSlots      = 1+MaxBlockShift - MinBlockShift;                 //!< alias
            typedef ClassLockPolicy   Policy;                                                          //!< alias
            class Code;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void * acquire(size_t & blockSize);
            virtual void   release(void * &blockAddr, size_t &blockSize) noexcept;
            virtual void   toXML(XML::Log &) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            //! acquire memory by its log2 size
            /**
             \param  blockShift MinBlockShift <= blockShift << MaxBlockShift
             \return block[2^blockShift]
             */
            void * acquireBlock(const unsigned blockShift);

            //! release memory
            /**
             \param blockAddr previously acquired
             \param blockShift blockAddr[2^blockShift]
             */
            void   releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept;

            //! specific garbage collector \param amount amount to free on each slot
            void gc(const uint8_t amount) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Archon); //!< discarded
            friend class Singleton<Archon,ClassLockPolicy>;
            Archon();           //!< setup
            ~Archon() noexcept; //!< cleanup
            Code * const code;  //!< inner code

        };
    }
}

#endif // !Y_Memory_Archon_Included

