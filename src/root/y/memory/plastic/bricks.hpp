
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
            //__________________________________________________________________
            //
            //
            //
            //! Manage bricks to pave and acquire/release blocks in a region
            //
            //
            //__________________________________________________________________
            class Bricks
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const size_t   BrickBytes   = sizeof(Brick);               //!< alias
                static const size_t   MinPerPage   = 1;                           //!< alias
                static const size_t   MinBlockSize = (2+MinPerPage) * BrickBytes; //!< head+memory+tail

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param pageAddr valid memory address
                 \param pageSize pageSize>=MinBlockSize
                 */
                Bricks(void * const pageAddr, const size_t pageSize) noexcept;

                //! cleanup
                ~Bricks() noexcept;

                //! check emptiness \return true if no acquired block
                bool areEmpty() const noexcept;

                //! try to acquire new block
                /**
                 \param blockSize query blockSize
                 \return a zeroed block with at least blockSize bytes, adjusted upon success
                 */
                void * acquire(size_t &blockSize) noexcept;


                //! release a block
                /**
                 \param blockAddr previously acquired block
                 \param blockSize previously acquired size
                 \return owning Bricks, fusioned block
                 */
                static Bricks * Release(void * & blockAddr,
                                        size_t & blockSize) noexcept;

                //! test owned brick (mostly to debug) \return true if brick is found
                bool ownsBrick(const Brick * const) const noexcept;


                size_t         ngap; //!< availalable gaps
                Brick * const  head; //!< head brick
                Brick * const  tail; //!< tail brick
                const size_t   maxBlockSize;
                Bricks * const next;
                Bricks * const prev;
                
            private:
                Y_Disable_Copy_And_Assign(Bricks); //!< discard

                //! prepare brick with optional split
                /**
                 \param brick     matching brick
                 \param blockSize input/output blockSize
                 \return zeroed block of blockSize bytes
                 */
                void * deliver(Brick * const brick, size_t &blockSize) noexcept;


            };
            
        }
    }

}

#endif // !Y_Memory_Plastic_Bricks_Included

