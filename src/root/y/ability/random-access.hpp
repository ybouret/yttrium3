
//! \file

#ifndef Y_RandomAccess_Included
#define Y_RandomAccess_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Random Access API...
    //
    //
    //__________________________________________________________________________
    class RandomAccess
    {
    public:

        explicit RandomAccess() noexcept {} //!< setup
        virtual ~RandomAccess() noexcept {} //!< cleanup

        virtual void remove(const size_t indx) noexcept        = 0;
        virtual void demote(const size_t indx) noexcept        = 0;
        

    private:
        Y_Disable_Copy_And_Assign(RandomAccess); //!< discarded
    };

}

#endif // !Y_RandomAccess_Included

