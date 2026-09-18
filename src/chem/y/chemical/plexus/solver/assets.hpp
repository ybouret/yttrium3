
//! \file

#ifndef Y_Chemical_Plexus_Assets_Included
#define Y_Chemical_Plexus_Assets_Included 1

#include "y/chemical/plexus/solver/algebra.hpp"
#include "y/coven/finder.hpp"
#include "y/mkl/minimize/api.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Assets : public Object
        {
        public:

            explicit Assets(const size_t n, const size_t m);
            virtual ~Assets() noexcept;


            MKL::Minimize::Engine<xreal_t> minimize;
            AutoPtr<Algebra>               algebra;
            AutoPtr<Coven::Finder>         finder;

        private:
            Y_Disable_Copy_And_Assign(Assets);
        };

    }

}

#endif // !Y_Chemical_Plexus_Assets_Included

