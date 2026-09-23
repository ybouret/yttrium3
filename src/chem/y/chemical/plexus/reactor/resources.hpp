//! \file

#ifndef Y_Chemical_Plexus_Reactor_Resources_Included
#define Y_Chemical_Plexus_Reactor_Resources_Included

#include "y/coven/finder.hpp"
#include "y/mkl/minimize/api.hpp"
#include "y/pointer/auto.hpp"
#include "y/chemical/plexus/reactor/algebra.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Resources : public Object
        {
        public:

            explicit Resources(const size_t N, const size_t M);
            virtual ~Resources() noexcept;

            AutoPtr<Coven::Finder>         finder;
            MKL::Minimize::Engine<xreal_t> minimize;
            AutoPtr<Algebra>               algebra;
            
        private:
            Y_Disable_Copy_And_Assign(Resources);
        };

    }

}

#endif // !Y_Chemical_Plexus_Reactor_Resources_Included

