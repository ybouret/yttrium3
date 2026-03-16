
//! \file

#ifndef Y_Derived_Included
#define Y_Derived_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    //! helper to avoid the use of *this in constructors
    class Derived
    {
    protected:
        explicit Derived() noexcept;

    public:
        virtual ~Derived() noexcept;

        template <typename PARENT> inline
        PARENT & as() noexcept
        {
            return *static_cast<PARENT *>(this);
        }

        template <typename PARENT> inline
        const PARENT & as() const noexcept
        {
            return *static_cast<const PARENT *>(this);
        }
        

    private:
        Y_Disable_Copy_And_Assign(Derived);
    };
}

#endif // !Y_Derived_Included
