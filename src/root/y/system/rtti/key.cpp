
#include "y/system/rtti/key.hpp"


namespace Yttrium
{

    RTTI:: Key:: Key(const Key &key) noexcept :
    AddrKey(key)
    {
    }


    RTTI:: Key:: ~Key() noexcept
    {
    }

    RTTI::Key:: Key(const std::type_info &ti) :
    AddrKey( RTTI::Of(ti) )
    {
        
    }

}
