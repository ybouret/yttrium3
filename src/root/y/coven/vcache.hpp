
//! \file

#ifndef Y_Coven_VCache_Included
#define Y_Coven_VCache_Included 1

#include "y/coven/vector.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/core/pool/cxx.hpp"
#include "y/core/list/cxx.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! List of vectors
        //
        //
        //______________________________________________________________________
        typedef CxxList<Vector> Vectors;

        //______________________________________________________________________
        //
        //
        //
        //! Cache of vectors for given dimensions
        //
        //
        //______________________________________________________________________
        class VCache :
        public Concurrent::Mutex,
        public Metrics,
        public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit VCache(const Metrics &); //!< setup from metrics
            virtual ~VCache()       noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Vector * query();                        //!< query \return cached/new vector
            void     store(Vector * const) noexcept; //!< store used vector

            //__________________________________________________________________
            //
            //
            // Interface 
            //
            //__________________________________________________________________
            virtual size_t count() const noexcept;
            virtual void   cache(const size_t);
            virtual void   gc(const uint8_t) noexcept;

        private:
            Y_Disable_Copy_And_Assign(VCache); //!< discarded
            CxxPool<Vector> vpool;             //!< inner cache
        };

    }

}

#endif // !Y_Coven_VCache_Included

