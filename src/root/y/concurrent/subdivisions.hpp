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
            explicit Subdivisions(const size_t) noexcept;
            virtual ~Subdivisions() noexcept;

            const size_t ncpu;

        private:
            Y_Disable_Copy_And_Assign(Subdivisions);
            //virtual const Subdivision & getSub(const size_t i)  const noexcept = 0;
        };

    }

}

#endif // !Y_Concurrent_Subdivisions_Included


