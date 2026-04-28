

//! \file

#ifndef Y_Dynamic_Included
#define Y_Dynamic_Included 1

#include "y/ability/expandable.hpp"
#include "y/ability/recyclable.hpp"


namespace Yttrium
{
    template <typename RELEASABLE>
    class Dynamic : public Expandable<RELEASABLE>, public Recyclable
    {
    public:
        inline explicit Dynamic() noexcept : Expandable<RELEASABLE>(), Recyclable() {}
        inline virtual ~Dynamic() noexcept {}
        
    private:
        Y_Disable_Copy_And_Assign(Dynamic);
    };

}
#endif // !Y_Dynamic_Included

