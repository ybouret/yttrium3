
//! \file

#ifndef Y_Chemical_Defs_Included
#define Y_Chemical_Defs_Included 1

#include "y/mkl/xreal.hpp"
#include "y/container/writable.hpp"
#include "y/cameo/multiplication.hpp"
#include "y/cameo/addition.hpp"
#include "y/mkl/triplet.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef double                         real_t;    //!< alias
        typedef XReal<double>                  xreal_t;   //!< alias
        typedef Readable<xreal_t>              XReadable; //!< alias
        typedef Writable<xreal_t>              XWritable; //!< alias
        typedef Cameo::Multiplication<xreal_t> XMul;      //!< alias
        typedef Cameo::Addition<xreal_t>       XAdd;      //!< alias
        typedef MKL::Triplet<xreal_t>          XTriplet;  //!< alias

        
    }

}

#endif // !Y_Chemical_Defs_Included
