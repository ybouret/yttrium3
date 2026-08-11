
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

            //__________________________________________________________________
            //
            //
            //
            //! Base class to share parallelism and local memory
            //
            //
            //__________________________________________________________________
            class Scheme
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________


                explicit Scheme(const size_t);   //!< setup parallelism and NEW local memory
                virtual ~Scheme() noexcept;      //!< cleanup
                Scheme(const Scheme &) noexcept; //!< duplicate, no-throw

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t parallelism; //!< parallelism > 0
                LocalMemory  localMemory; //!< shared local memory

            private:
                Y_Disable_Assign(Scheme); //!< discarded
            };
        }

    }

}

#endif // !Y_Concurrent_Splitting_Scheme_Included

