
//! \file

#ifndef Y_Memory_Plastic_Forge_Included
#define Y_Memory_Plastic_Forge_Included 1

#include "y/memory/plastic/bricks.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/metrics.hpp"
#include "y/calculus/meta2.hpp"
#include "y/core/meta-max.hpp"
#include "y/core/list.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{
    class Lockable;

    namespace Memory
    {
        class Book;
        namespace Plastic
        {

            //__________________________________________________________________
            //
            //
            //
            //! Forge of bricks
            /**
             - LEVEL-1 cache of bricks built upon Pages from Book
             */
            //
            //__________________________________________________________________
            class Forge : public Allocator
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const size_t          DataOffset   = Alignment::To<Brick>::CeilOf<sizeof(Bricks)>::Value; //!< offset of data
                static const size_t          MinimalSize  = DataOffset + Bricks::MinUserBytes;                   //!< to handle minimal data
                static const size_t          MinRawBytes  = MetaNextPowerOfTwo<MinimalSize>::Value;              //!< alias
                static const size_t          MinPageBytes = MetaMax<MinRawBytes,Metrics::DefaultBytes>::Value;   //!< alias
                static const unsigned        MinPageShift = IntegerLog2<MinPageBytes>::Value;                    //!< alias
                static const size_t          MaxPageBytes = Metrics::MaxPageBytes;                               //!< alias
                static const unsigned        MaxPageShift = Metrics::MaxPageShift;                               //!< alias
                static const size_t          ReservedSize = DataOffset + Bricks::Reserved;                       //!< alias
                static const size_t          MaxBlockSize = MaxPageBytes - ReservedSize;                         //!< alias
                static const size_t          DefaultMaxBlockSize = Memory::Metrics::DefaultBytes - ReservedSize; //!< alias
                typedef Core::ListOf<Bricks> ListType; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setuo
                /**
                 \param userBook PERSISTENT provider of Pages
                 \param userLock PERSISTENT access control
                 */
                explicit Forge(Book     &userBook,
                               Lockable &userLock) noexcept;

                //! cleanup
                virtual ~Forge() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! acquire a new block of memory
                /**
                 \param blockSize 0 <= blockSize <= MaxBlockSize
                 \return new zeroed block, updated blockSize
                 */
                virtual void *   acquire(size_t & blockSize);
                virtual void     release(void * &blockAddr,
                                         size_t &blockSize) noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                //!
                /**
                 \param blockSize 0 <= blockSize <= MaxBlockSize
                 \return shift for Bricks able to host blockSize
                 */
                static unsigned ShiftFor(const size_t blockSize) noexcept;

                //! acquire block
                /**
                 \param blockSize minimal block size
                 \return acquired memory
                 */
                void * legacyAcquire(const size_t blockSize);

                //! release block with automatic blockSize retrieval
                /**
                 \param blockAddr previously acquired block
                 */
                void   legacyRelease(void * const blockAddr) noexcept;


                //! access to check status \return &list
                const ListType * operator->() const noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                ListType list;    //!< LRU bricks
                Bricks * empty;   //!< none or first empty

            public:
                Book     & book;    //!< PERSISTENT book of Pages
                Lockable & access;  //!< PERSISTENT access

            private:
                Y_Disable_Copy_And_Assign(Forge); //!< discarded

                //! return Bricks to book
                void     remove(Bricks * const) noexcept;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                Bricks * newBricks(const unsigned shift);
                Bricks * newBricksFor(const size_t blockSize);
                void     postRelease(Bricks * node) noexcept;
#endif
            };

        }
    }
}

#endif // !Y_Memory_Plastic_Forge_Included

