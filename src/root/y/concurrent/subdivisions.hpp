//! \file

#ifndef Y_Concurrent_Subdivisions_Included
#define Y_Concurrent_Subdivisions_Included 1

#include "y/concurrent/subdivision.hpp"
#include "y/concurrent/splitting/scheme.hpp"

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
        class Subdivisions : public Splitting::Scheme
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup parallelism and new local memory
            explicit Subdivisions(const size_t);

            //! setup by no-throw copy of scheme
            explicit Subdivisions(const Splitting::Scheme &) noexcept;

            //! cleanup
            virtual ~Subdivisions() noexcept; 


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

            

        private:
            Y_Disable_Copy_And_Assign(Subdivisions); //!< discarded


        };

    }

}

#endif // !Y_Concurrent_Subdivisions_Included


