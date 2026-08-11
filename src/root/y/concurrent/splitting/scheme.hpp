
//! \file

#ifndef Y_Concurrent_Splitting_Scheme_Included
#define Y_Concurrent_Splitting_Scheme_Included 1

#include "y/concurrent/api/local/memory.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {

            class Scheme
            {
            public:

                //! setup parallelism
                explicit Scheme(const size_t);
                virtual ~Scheme() noexcept;
                Scheme(const Scheme &) noexcept;

                const size_t parallelism; //!< parallelism > 0
                LocalMemory  localMemory; //!< shared local memory

            private:
                Y_Disable_Assign(Scheme);
            };
        }

    }

}

#endif // !Y_Concurrent_Splitting_Scheme_Included

