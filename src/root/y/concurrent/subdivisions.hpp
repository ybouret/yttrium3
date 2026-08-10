//! \file

#ifndef Y_Concurrent_Subdivisions_Included
#define Y_Concurrent_Subdivisions_Included 1

#include "y/concurrent/subdivision.hpp"
#include "y/concurrent/api/local/memory.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Subdivision interface
        //
        //
        //______________________________________________________________________
        class Subdivisions
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Subdivisions(const size_t);                               //!< setup with ncpu, create a a new local memory
            explicit Subdivisions(const size_t, const LocalMemory &) noexcept; //!< setup with ncpu and an existing local memory
            virtual ~Subdivisions()                                  noexcept; //!< cleanup


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________


            virtual const Subdivision & sub(const size_t) const noexcept = 0; //!< \return subdivision in [1:ncpu]
            Subdivision &               sub(const size_t)       noexcept;     //!< \return subdivision in [1:ncpu]

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            void updateLocalCaches() noexcept;           //!< update local caches from shared memory
            void removeLocalCaches() noexcept;           //!< remove all local caches, keep shared memory
            void ensureLocalCaches(const size_t bytes); //!< check memory and update

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t ncpu;  //!< dimensions
            LocalMemory  shmm;  //!< shared memory manager

        private:
            Y_Disable_Copy_And_Assign(Subdivisions); //!< discarded


        };

    }

}

#endif // !Y_Concurrent_Subdivisions_Included


