
//! file

#ifndef Y_InputStream_Included
#define Y_InputStream_Included


#include "y/config/setup.hpp"

namespace Yttrium
{

    class InputStream
    {

    public:
        explicit InputStream() noexcept;
        virtual ~InputStream() noexcept;

    private:
        Y_Disable_Copy_And_Assign(InputStream);
    };

}


#endif // !Y_InputStream_Included
