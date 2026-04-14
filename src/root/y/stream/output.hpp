//! file

#ifndef Y_OutputStream_Included
#define Y_OutputStream_Included


#include "y/config/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for output stream
    //
    //
    //__________________________________________________________________________
    class OutputStream
    {

    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit OutputStream() noexcept; //!< setup
        virtual ~OutputStream() noexcept; //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(OutputStream); //!< discarded
    };

}


#endif // !Y_OutputStream_Included
