//! file

#ifndef Y_InputStream_Included
#define Y_InputStream_Included


#include "y/config/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for input stream
    //
    //
    //__________________________________________________________________________
    class InputStream
    {

    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit InputStream() noexcept; //!< setup
        virtual ~InputStream() noexcept; //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarded
    };

}


#endif // !Y_InputStream_Included
