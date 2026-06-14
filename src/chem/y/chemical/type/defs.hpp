
//! \file

#ifndef Y_Chemical_Defs_Included
#define Y_Chemical_Defs_Included 1

#include "y/mkl/xreal.hpp"
#include "y/container/writable.hpp"
#include "y/cameo/multiplication.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef double                         real_t;
        typedef XReal<double>                  xreal_t;
        typedef Readable<xreal_t>              XReadable;
        typedef Writable<xreal_t>              XWritable;
        typedef Cameo::Multiplication<xreal_t> XMul;

    }

}

#endif // !Y_Chemical_Defs_Included
