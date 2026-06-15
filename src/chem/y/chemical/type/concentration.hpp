
//! \file

#ifndef Y_Chemical_Concentration_Included
#define Y_Chemical_Concentration_Included 1

#include "y/chemical/type/defs.hpp"
#include "y/random/uniform32.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        struct Concentration
        {
            static const int MinLog10 = -20;
            static const int MaxLog10 =   1;
            static xreal_t   Get(Random::Uniform32 &ran,
                                 const real_t       probaZ = 0) noexcept;

            static void Fill(Random::Uniform32 &, XWritable &, const size_t, const real_t probaZ=0) noexcept;

        };
    }

}

#endif // !Y_Chemical_Concentration_Included
