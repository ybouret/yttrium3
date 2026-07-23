
//! \file

#ifndef Y_Concurrent_Splitting_UDTS_Included
#define Y_Concurrent_Splitting_UDTS_Included 1

#include "y/concurrent/splitting/udt.hpp"
#include "y/concurrent/subdivisions.hpp"
#include "y/container/contiguous/writable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {

            //__________________________________________________________________
            //
            //
            //
            //! Set of Upper Diagonal Tiles
            //
            //
            //__________________________________________________________________
            class UpperDiagonalTiles :
            public Subdivisions,
            public ContiguousWritable<UpperDiagonalTile>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                class Code;
                typedef UpperDiagonalTile Tile; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with empty tiles
                /**
                 \param mySize number of tiles
                 \param access persistent access
                 */
                explicit UpperDiagonalTiles(const size_t mySize,
                                            Lockable &   access);

                //! cleanup
                virtual ~UpperDiagonalTiles() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual const Tile &sub(const size_t) const noexcept;
                virtual size_t      size()            const noexcept;
                virtual size_t      capacity()        const noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! remap tiles
                /**
                 \param extent (new) matrix size
                 \param access persistent lock
                 */
                void remap(const size_t extent, Lockable &access) noexcept;


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTiles);
                Code * const code;
                virtual const Tile & ask(const size_t indx) const noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };
        }

    }

}

#endif // !Y_Concurrent_Splitting_UDTS_Included

