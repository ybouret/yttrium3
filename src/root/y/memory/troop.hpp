//! \file

#ifndef Y_Memory_Troop_Included
#define Y_Memory_Troop_Included 1

#include "y/memory/allocator/proxy.hpp"
#include "y/type/args.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T,
        typename BASE_CLASS = Object>
        class TroopOf : public BASE_CLASS
        {
        public:
            Y_Args_Expose(T,Type);
            
            size_t        bytes;
            size_t        count;
            MutableType * addr;
            MutableType * cxx;

        private:
            Y_Disable_Copy_And_Assign(TroopOf);
        };

    }
}

#endif // !Y_Memory_Troop_Included

