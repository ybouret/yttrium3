
//! \file

#ifndef Y_System_RTTI_Key_Included
#define Y_System_RTTI_Key_Included 1

#include "y/system/rtti.hpp"
#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! RTTI as Key for Associative Containers
    //
    //
    //__________________________________________________________________________
    class RTTI::Key : public AddrKey
    {
    public:
        Key(const std::type_info &); //!< setup from unique RTTI
        Key(const Key &) noexcept;   //!< duplicate
        virtual ~Key()   noexcept;   //!< cleanup

    private:
        Y_Disable_Assign(Key); //!< discarded
    };
}

#endif // !Y_System_RTTI_Key_Included
