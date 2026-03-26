
//! \file

#ifndef Y_Memory_Allocator_Dyadic_Included
#define Y_Memory_Allocator_Dyadic_Included 1

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
        //! Memory Dyadic allocator, aliased on Concurrent::Nucleus
        /**
         - uses nucleus.book for "large" blocks
         - uses nucleus.blocks for "small" blocks
         */
        //
        //______________________________________________________________________
        class Dyadic :
        public Singleton<Dyadic,ClassLockPolicy>,
        public Allocator
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const               CallSign;                             //!< "Memory::Dyadic"
            static const System::AtExit::Longevity  LifeTime = LifeTimeFor::MemoryDyadic; //!< longevity
            typedef ClassLockPolicy                 Policy;                               //!< alias
            class Code;

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

            //! acquire specific block \param shift for 2^shift bytes \return found block
            void * acquireBlock(const unsigned shift);

            //! release specific block \param entry acquire block \param shift 2^shift bytes
            void   releaseBlock(void * const entry, const unsigned shift) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Dyadic); //!< discarded
            friend class Singleton<Dyadic,Policy>;

            explicit Dyadic();          //!< setup
            virtual ~Dyadic() noexcept; //!< cleanup
        };

    }
}

#endif // !Y_Memory_Allocator_Dyadic_Included

