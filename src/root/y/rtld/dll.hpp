//! \file

#ifndef Y_RTLD_DLL_Included
#define Y_RTLD_DLL_Included 1

#include "y/string.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{

    class DLL : public CountedObject
    {
    public:
        class Code;
        
        virtual ~DLL() noexcept;
        
    private:
        Y_Disable_Assign(DLL);
        Code * const code;
    };

}

#endif // !Y_RTLD_DLL_Included

