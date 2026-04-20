
//! \file

#ifndef Y_CxxContainer_Included
#define Y_CxxContainer_Included 1

#include "y/object.hpp"

namespace Yttrium
{
    class CxxContainer : public Object
    {
    public:
        explicit CxxContainer(const size_t) noexcept;
        virtual ~CxxContainer()             noexcept;

        const size_t size;
    private:
        Y_Disable_Copy_And_Assign(CxxContainer);
    };
}

#endif // !Y_CxxContainer_Included


