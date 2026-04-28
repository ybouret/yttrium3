

//! \file

#ifndef Y_Dynamic_Included
#define Y_Dynamic_Included 1

#include "y/ability/expandable.hpp"
#include "y/ability/recyclable.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Dynamic interface
    //
    //
    //__________________________________________________________________________
    template <typename RELEASABLE>
    class Dynamic : public Expandable<RELEASABLE>, public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit Dynamic() noexcept : Expandable<RELEASABLE>(), Recyclable() {}

        //! cleanup
        inline virtual ~Dynamic() noexcept {}
        
    private:
        Y_Disable_Copy_And_Assign(Dynamic); //!< discarded
    };

}
#endif // !Y_Dynamic_Included

