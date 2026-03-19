
//! \file

#ifndef Y_Memory_Plastic_Forge_Included
#define Y_Memory_Plastic_Forge_Included 1

#include "y/memory/plastic/bricks.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/metrics.hpp"
#include "y/calculus/meta2.hpp"
#include "y/core/meta-max.hpp"
#include "y/core/list.hpp"

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
             - LEVEL-1 cache of bricks built upon Page
             */
            //
            //__________________________________________________________________
            class Forge
            {
            public:
                static const size_t   DataOffset   = Alignment::To<Brick>::CeilOf<sizeof(Bricks)>::Value;
                static const size_t   MinRawBytes  = MetaMax<DataOffset + Bricks::MinUserBytes,Metrics::MinPageBytes>::Value;
                static const size_t   MinPageBytes = MetaNextPowerOfTwo<MinRawBytes>::Value;
                static const unsigned MinPageShift = IntegerLog2<MinPageBytes>::Value;
                static const size_t   MaxPageBytes = Metrics::MaxPageBytes;
                static const unsigned MaxPageShift = Metrics::MaxPageShift;


                explicit Forge(Book     &userBook,
                               Lockable &userLock) noexcept;

                virtual ~Forge() noexcept;

                static unsigned ShiftFor(const size_t blockSize);

                void * acquire(size_t & blockSize);


            private:
                Bricks *             last;
                Core::ListOf<Bricks> list;

            public:
                Book               & book;    //!< PERSISTENT pages
                Lockable           & access;  //!< PERSISTENT access

            private:
                Y_Disable_Copy_And_Assign(Forge);

                Bricks * newBricks(const unsigned shift);

            };

        }
    }
}

#endif // !Y_Memory_Plastic_Forge_Included

