
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
        //! Memory Global allocator, aliased on Concurrent::Nucleus
        //
        //
        //______________________________________________________________________
        class Dyadic :
        public Singleton<Dyadic,ClassLockPolicy>,
        public Allocator
        {
        public:
            static const char * const               CallSign;                             //!< "Memory::Dyadic"
            static const System::AtExit::Longevity  LifeTime = LifeTimeFor::MemoryDyadic; //!< longevity
            typedef ClassLockPolicy                 Policy;                               //!< alias
            class Code;

            virtual void * acquire(size_t &);
            virtual void   release(void * &, size_t &) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Dyadic); //!< discarded
            friend class Singleton<Dyadic,Policy>;

            explicit Dyadic();          //!< setup
            virtual ~Dyadic() noexcept; //!< cleanup
        };

    }
}

#endif // !Y_Memory_Allocator_Dyadic_Included

