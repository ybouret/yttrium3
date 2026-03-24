
//! \file

#ifndef Y_Memory_Small_Blocks_Included
#define Y_Memory_Small_Blocks_Included 1

#include "y/memory/small/house.hpp"
#include "y/calculus/meta2.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Small
        {
            //__________________________________________________________________
            //
            //
            //
            //! Multiple arenas for multiple block sizes
            //
            //
            //__________________________________________________________________
            class Blocks
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Core::ListOf<Arena> Slot;  //!< alias
                static const size_t         BytesPerSlot = sizeof(Slot);                                         //!< alias
                static const size_t         DefaultBytes = Y_BLOCK_SIZE;                                         //!< inner static memory hint
                static const size_t         TableSize    = MetaPrevPowerOfTwo<DefaultBytes/BytesPerSlot>::Value; //!< inner static memory
                static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;                        //!< log2(TableSize)
                static const size_t         TableMask    = TableSize-1;                                          //!< x%TableSize == x&TableMask
                static const size_t         TableBytes   = TableSize * sizeof(Slot);                             //!< actual table bytes request
                static const size_t         TableWords   = Alignment::WordsGEQ<TableBytes>::Count;               //!< inner table words

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                //! setup
                /**
                 \param userBook repository of pages for inner arenas
                 \param userLock locking for this AND each newly created arena
                 */
                explicit Blocks(Memory::Book & userBook,
                                Lockable     & userLock) noexcept;

                //! cleanup
                virtual ~Blocks() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! acquire a new/cached block
                /**
                 \param blockSize 1 <= blockSize <= Arena::MaxBlockSize
                 \return a new, zeroed block
                 */
                void * acquire(const size_t blockSize);

                //! release a previously acquired block
                /**
                 \param blockAddr block address
                 \param blockSize block size
                 */
                void   release(void * const blockAddr, const size_t blockSize) noexcept;


                Arena & operator[](const size_t blockSize);

                //! check ownership
                /**
                 \param blockAddr address to look for
                 \param blockSize updated if found
                 \return true iff blockAddr within one of arena
                 */
                bool   owns(const void * const blockAddr, size_t &blockSize) const noexcept;

            private:
                Y_Disable_Copy_And_Assign(Blocks); //!< discarding

                Slot * const   table;            //!< hash table for arenas
                Arena *        acquiring;        //!< top-level caching
                Arena *        releasing;        //!< top-level caching
                Memory::Book & book;             //!< PERSISTENT book
                Arena          arena;            //!< dedicated arena( sizeof(Arena) ) to create specific arenas
                House<Arena>   house;            //!< helper to setup arenas
                void *         wksp[TableWords]; //!< inner static memory
            };
        }

    }

}

#endif // !Y_Memory_Small_Blocks_Included
