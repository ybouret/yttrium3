//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"
#include "y/memory/allocator.hpp"
#include "y/memory/page/factory.hpp"

namespace Yttrium
{
    class Lockable;
    namespace Memory { class Book; }

    namespace Concurrent
    {
        class SystemMutex;
        class SystemCondition;

        //______________________________________________________________________
        //
        //
        //
        //! Nucleus to store internal concurrency basics
        //
        //
        //______________________________________________________________________
        class Nucleus :
        public Singulet,
        public Memory::Allocator,
        public Memory::PageFactory
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                    //!< "Nucleus"
            static const Longevity    LifeTime = GreatestLifeTime; //!< alias
            class Code;
            class Data;
            
            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char *   callSign() const noexcept;
            virtual Longevity      lifeTime() const noexcept;
            virtual void *         acquire(size_t & blockSize);
            virtual void           release(void * & blockAddr, size_t &blockSize) noexcept;

            //! thread-safe, size-restricted page allocation
            /**
             \param shift MinPageShift <= shift <= MaxPageShift
             \return a zeroed page with 2^shift bytes
             */
            virtual Memory::Page * acquirePage(const unsigned shift);
            virtual void           releasePage(Memory::Page * const page, const unsigned shift) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static  Nucleus &  Instance();          //!< handle instance \return single Nucleus
            static  Nucleus &  Location() noexcept; //!< current location \return existing instance


            SystemMutex * acquireSystemMutex();                             //!< inner acquire/setup \return ready system mutex
            void          releaseSystemMutex(SystemMutex * const) noexcept; //!< clear/release system mutex

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            static const uint64_t & RAM; //!< bookkeeping of allocated memory

        private:
            Y_Disable_Copy_And_Assign(Nucleus); //!< discarded
            explicit Nucleus();                 //!< setup internal code
            virtual ~Nucleus() noexcept;        //!< cleanup internal code
            Code * const code;                  //!< inner code
            Data * const data;                  //!< inner data
            
            static void          SelfDestruct(void * const) noexcept; //!< call destructor at exit
            void                 destructCode()             noexcept; //!< destruct inner code
            Memory::PageFactory &factory()                  noexcept; //!< avoid this in constructor \return *this

        public:
            Lockable     & access; //!< reference to inner, global mutex
            Memory::Book & book;   //!< reference to inner book
        };

    }
}

#endif // !Y_Concurrent_Nucleus_Included

