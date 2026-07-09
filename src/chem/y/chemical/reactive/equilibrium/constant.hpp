

//! \file

#ifndef Y_Chemical_ConstantEquilibrium_Included
#define Y_Chemical_ConstantEquilibrium_Included 1

#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Constant equilibrium
        //
        //
        //______________________________________________________________________
        class ConstantEquilibrium : public Equilibrium
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ConstantEquilibrium(const String &, const size_t, const xreal_t); //!< setup
            virtual ~ConstantEquilibrium() noexcept; //!< cleanup

            
        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(ConstantEquilibrium);
            virtual xreal_t getK(const xreal_t);
            const xreal_t K_;
#endif
        };

    }

}

#endif // !Y_Chemical_ConstantEquilibrium_Included

