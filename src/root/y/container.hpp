//! \file

#ifndef Y_Container_Included
#define Y_Container_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for containers
    //
    //
    //__________________________________________________________________________
    class Container
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Container() noexcept;

    public:
        virtual ~Container() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual size_t size()     const noexcept = 0; //!< \return current item count
        virtual size_t capacity() const noexcept = 0; //!< \return maximum item count

    private:
        Y_Disable_Copy_And_Assign(Container); //!< discarded
    };

}

#endif // !Y_Container_Included

