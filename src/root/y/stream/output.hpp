

//! file

#ifndef Y_OutputStream_Included
#define Y_OutputStream_Included


#include "y/config/setup.hpp"

namespace Yttrium
{

    class OutputStream
    {

    public:
        explicit OutputStream() noexcept;
        virtual ~OutputStream() noexcept;

    private:
        Y_Disable_Copy_And_Assign(OutputStream);
    };

}


#endif // !Y_OutputStream_Included
