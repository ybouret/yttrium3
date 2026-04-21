

//! \file

#ifndef Y_ContiguousReadable_Included
#define Y_ContiguousReadable_Included 1

#include "y/container/contiguous/ro.hpp"
#include "y/container/readable.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Default Contiguous interface
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class ContiguousReadable : public ReadOnlyContiguous< Readable<T> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit ContiguousReadable() noexcept : ReadOnlyContiguous< Readable<T> >() {}

        //! cleanup
        inline virtual ~ContiguousReadable() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(ContiguousReadable); //!< discarded
    };
}

#endif // !Y_ContiguousReadable_Included
