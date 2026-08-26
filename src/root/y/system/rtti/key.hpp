
//! \file

#ifndef Y_System_RTTI_Key_Included
#define Y_System_RTTI_Key_Included 1

#include "y/system/rtti.hpp"
#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{


    class RTTI::Key : public AddrKey
    {
    public:
        Key(const std::type_info &);
        Key(const Key &) noexcept;
        virtual ~Key()   noexcept;
    private:
        Y_Disable_Assign(Key);
    };
}

#endif // !Y_System_RTTI_Key_Included
