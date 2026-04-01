
//! \file

#ifndef Y_Memory_Allocator_Pooled_Included
#define Y_Memory_Allocator_Pooled_Included 1

#include "y/memory/allocator.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Memory Pooled allocator, alias to inner Plastic::Forge
        //
        //
        //______________________________________________________________________
        class Pooled :
        public Singleton<Pooled,ClassLockPolicy>,
        public Allocator
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const               CallSign;                             //!< "Memory::Global"
            static const System::AtExit::Longevity  LifeTime = LifeTimeFor::MemoryPooled; //!< longevity

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void * acquire(size_t &);
            virtual void   release(void * &, size_t &) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! acquire memory
            /**
             \param  blockSize minimal byte count
             \return blockAddr
             */
            void * legacyAcquire(const size_t blockSize);

            //! release memory, with automatic retrieving of block size
            /**
             \param blockAddr acquired memory
             */
            void   legacyRelease(void * const blockAddr) noexcept;


        private:
            Y_Disable_Copy_And_Assign(Pooled); //!< discarded
            friend class Singleton<Pooled,ClassLockPolicy>;

            explicit Pooled();          //!< setup
            virtual ~Pooled() noexcept; //!< cleanup
        };

    }
}

#endif // !Y_Memory_Allocator_Pooled_Included

