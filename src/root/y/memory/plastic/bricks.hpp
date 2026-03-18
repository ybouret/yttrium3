
//! \file

#ifndef Y_Memory_Plastic_Bricks_Included
#define Y_Memory_Plastic_Bricks_Included 1

#include "y/memory/plastic/brick.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Plastic
        {
            
            class Bricks
            {
            public:
                static const size_t   BrickBytes   = sizeof(Brick);
                static const size_t   MinPerPage   = 1;
                static const size_t   MinBlockSize = (2+MinPerPage) * BrickBytes;
                
                Bricks(void * const pageAddr, const size_t pageSize) noexcept;
                ~Bricks() noexcept;

                bool areEmpty() const noexcept;

                void * acquire(size_t &blockSize) noexcept;
                void * deliver(Brick * const brick, size_t &blockSize) noexcept;


                size_t        ngap; //!< availalable gaps
                Brick * const head; //!< head brick
                Brick * const tail; //!< tail brick

            private:
                Y_Disable_Copy_And_Assign(Bricks);


            };
            
        }
    }

}

#endif // !Y_Memory_Plastic_Bricks_Included

