
//! file

#ifndef Y_Serializable_Included
#define Y_Serializable_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    class OutputStream;
    
    class Serializable
    {
    public:
        explicit Serializable() noexcept;
        virtual ~Serializable() noexcept;

        virtual size_t serialize(OutputStream &) const = 0;

    private:
        Y_Disable_Copy_And_Assign(Serializable);
    };

}

#endif // !Y_Serializable_Included

