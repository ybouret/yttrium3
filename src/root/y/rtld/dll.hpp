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

        DLL(const String &);
        DLL(const char * const);
        DLL(const DLL &) noexcept;
        virtual ~DLL()   noexcept;

    private:
        Y_Disable_Assign(DLL);
        Code * const code;
    public:
        const String &name;
    };

}

#endif // !Y_RTLD_DLL_Included

