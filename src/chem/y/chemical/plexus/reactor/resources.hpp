//! \file

#ifndef Y_Chemical_Plexus_Reactor_Resources_Included
#define Y_Chemical_Plexus_Reactor_Resources_Included

#include "y/coven/finder.hpp"
#include "y/pointer/auto.hpp"
#include "y/chemical/plexus/reactor/algebra.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Resources for Reactor
        //
        //
        //______________________________________________________________________
        class Resources : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param N primary eqs \param M species count
            explicit Resources(const size_t N, const size_t M);

            //! cleanup
            virtual ~Resources() noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            AutoPtr<Coven::Finder>         finder;   //!< basis finder
            AutoPtr<Algebra>               algebra;  //!< algebraic ops
            
        private:
            Y_Disable_Copy_And_Assign(Resources); //!< discarded
        };

    }

}

#endif // !Y_Chemical_Plexus_Reactor_Resources_Included

