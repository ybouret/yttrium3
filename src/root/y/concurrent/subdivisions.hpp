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
            explicit Subdivisions(const size_t) noexcept; //!< setup with ncpu
            virtual ~Subdivisions()             noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t ncpu; //!< dimensions

        private:
            Y_Disable_Copy_And_Assign(Subdivisions); //!< discarded

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! \return subdivision in [1:ncpu]
            virtual const Subdivision & getSub(const size_t) const noexcept = 0;
        };

    }

}

#endif // !Y_Concurrent_Subdivisions_Included


