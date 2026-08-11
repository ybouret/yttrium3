
//! \file

#ifndef Y_Concurrent_Splitting_Tiles2D_Included
#define Y_Concurrent_Splitting_Tiles2D_Included 1

#include "y/concurrent/subdivisions.hpp"
#include "y/concurrent/splitting/tile2d.hpp"
#include "y/container/contiguous/writable.hpp"
#include "y/memory/troop.hpp"
#include "y/type/destroy.hpp"
#include "y/object.hpp"

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
            //! 2D (reusable) Tiles
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles2D :
            public Leap2D<T>,
            public Subdivisions,
            public ContiguousWritable< Tile2D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T>                     vertex_t; //!< alias
                typedef Leap2D<T>                  Leap;     //!< alias
                typedef Tile2D<T>                  Tile;     //!< alias
                typedef Memory::Troop<Tile,Object> Code;     //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param init threads or scheme
                 \param sync PERSISTENT lock
                 \param lo   lower coordinate
                 \param up   upper coordinate
                 */
                template <typename INITIALIZER>
                inline explicit Tiles2D(const INITIALIZER   &init,
                                        Lockable            &sync,
                                        const vertex_t       lo,
                                        const vertex_t       up) :
                Leap(lo,up),
                Subdivisions(init),
                code( new Code(parallelism) )
                {
                    setup(sync);
                }

                //! setup empty
                /**
                 \param init threads or scheme
                 \param sync PERSISTENT lock
                 */
                template <typename INITIALIZER>
                inline explicit Tiles2D(const INITIALIZER &init,
                                        Lockable          &sync) :
                Leap(),
                Subdivisions(init),
                code( new Code(parallelism) )
                {
                    setup(sync);
                }

                //! cleanup
                inline virtual ~Tiles2D() noexcept {
                    assert(code); Destroy(code);
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t              size()                 const noexcept { return parallelism; }
                inline virtual size_t              capacity()             const noexcept { return parallelism; }
                inline virtual const Subdivision & sub(const size_t indx) const noexcept
                {
                    return ask(indx);
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! remap if necessary
                /**
                 \param lo new lower
                 \param up new upper
                 \param lk PERSISTENT sync for each tile
                 */
                inline void remap(const vertex_t lo,
                                  const vertex_t up,
                                  Lockable      &lk) noexcept
                {
                    {
                        Leap &     self = *this;
                        const Leap next(lo,up);
                        if(next == self) return;
                        Coerce(self.lower) = next.lower;
                        Coerce(self.upper) = next.upper;
                        Coerce(self.width) = next.width;
                        Coerce(self.items) = next.items;
                    }
                    setup(lk); // metrics has changed
                }

                
            private:
                Y_Disable_Copy_And_Assign(Tiles2D); //!< discarded
                Code * const code;                  //!< inner code
               

                inline virtual const Tile & ask(const size_t indx) const noexcept
                {
                    assert(code);
                    assert(parallelism==code->size);
                    assert(indx>=1);
                    assert(indx<=parallelism);
                    return code->cxx[indx];
                }

                //! (re)create all tiles \param sync PERSISTENT sync for each tile
                inline void setup(Lockable &sync) noexcept
                {
                    assert(code);
                    code->free();
                    Tile * tile = code->addr;
                    while(code->size<parallelism)
                    {
                        new (tile++) Tile(parallelism,Coerce(code->size)++,sync,*this);
                    }
                    assert(parallelism==code->size);
                    updateLocalCaches();
                }
            };


        }
    }

}

#endif // !Y_Concurrent_Splitting_Tiles2D_Included

