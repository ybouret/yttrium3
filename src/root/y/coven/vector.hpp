
//! \file

#ifndef Y_Coven_Vector_Included
#define Y_Coven_Vector_Included 1

#include "y/coven/metrics.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Coven
    {

        typedef CxxArray<apz> IVector;

        class Vector : public Object, public Metrics, public IVector
        {
        public:
            explicit Vector(const Metrics&);
            virtual ~Vector() noexcept;
            Vector(const Vector &);
            Vector & operator=(const Vector &);
            
            void update();

            const size_t ncof; //!< number of non-zero coefs
            const apn    mod2; //!< norm2
            Vector *     next;
            Vector *     prev;

        };


    }

}

#endif // !Y_Coven_Vector_Included

