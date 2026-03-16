//! \file

//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/memory/small/arena.hpp"
#include "y/type/args.hpp"


namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            template <typename T>
            class HouseOf
            {
            public:
                Y_Args_Expose(T,Type);

                explicit HouseOf();


            private:
                Y_Disable_Copy_And_Assign(HouseOf);
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
