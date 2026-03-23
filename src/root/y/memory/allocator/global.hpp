//! \file

#ifndef Y_Memory_Allocator_Global_Included
#define Y_Memory_Allocator_Global_Included 1

#include "y/memory/allocator.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/singleton/alias-lock-policy.hpp"
#include "y/concurrent/nucleus.hpp"
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
        class Global :
        public Singleton<Global, AliasLockPolicy<Concurrent::Nucleus> >,
        public Allocator
        {
        public:
            static const char * const                    CallSign;                             //!< "Memory::Global"
            static const System::AtExit::Longevity       LifeTime = LifeTimeFor::MemoryGlobal; //!< longevity
            typedef AliasLockPolicy<Concurrent::Nucleus> Policy;                               //!< alias

            virtual void * acquire(size_t &);
            virtual void   release(void * &, size_t &) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Global); //!< discarded
            friend class Singleton<Global,Policy>;

            explicit Global();          //!< setup
            virtual ~Global() noexcept; //!< cleanup
        };

    }
}

#endif // !Y_Memory_Allocator_Global_Included

