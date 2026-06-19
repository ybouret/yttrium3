
//! \file

#ifndef Y_Chemical_Concentration_Included
#define Y_Chemical_Concentration_Included 1

#include "y/chemical/type/defs.hpp"
#include "y/random/uniform32.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Helper to create sets of concentrations
        //
        //
        //______________________________________________________________________
        struct Concentration
        {
            static const int MinLog10 = -20; //!< alias
            static const int MaxLog10 =   1; //!< alias

            //! get a random concentration
            /**
             \param ran prng
             \param probaZ add probability of zero concentration
             \return random concentration on 10^MinLog10:10^MaxLog10, 0 with probaZ
             */
            static xreal_t   Get(Random::Uniform32 &ran,
                                 const real_t       probaZ = 0) noexcept;

            //! (partially) fill an array of concentration \param probaZ probability of zero concentration
            static void Fill(Random::Uniform32 &, XWritable &, const size_t, const real_t probaZ=0) noexcept;

        };
    }

}

#endif // !Y_Chemical_Concentration_Included
