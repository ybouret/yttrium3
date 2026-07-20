//! \file

#ifndef Y_Concurrent_Subdivisions_Included
#define Y_Concurrent_Subdivisions_Included 1

#include "y/concurrent/subdivision.hpp"

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
            explicit Subdivisions(const size_t) noexcept; //!< setup with ncpu and persistent lock
            virtual ~Subdivisions()             noexcept; //!< cleanup


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

            void deleteCache()   noexcept;
            void ensureCache(const size_t bytesPerSubdivision);
            void updateCache() noexcept;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t ncpu; //!< dimensions
            
        private:
            Y_Disable_Copy_And_Assign(Subdivisions); //!< discarded
            void noCache() noexcept;
            
            const size_t wlen; //!< cache memory length
            void * const wksp; //!< cache memory address


        };

    }

}

#endif // !Y_Concurrent_Subdivisions_Included


