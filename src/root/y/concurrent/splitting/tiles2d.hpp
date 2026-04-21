
//! \file

#ifndef Y_Concurrent_Splitting_Tiles2D_Included
#define Y_Concurrent_Splitting_Tiles2D_Included 1

#include "y/concurrent/splitting/tile2d.hpp"
#include "y/memory/troop.hpp"
#include "y/container/contiguous/readable.hpp"
#include "y/type/destroy.hpp"


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
            public ContiguousReadable< Tile2D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T>              vertex_t;
                typedef Leap2D<T>           Leap; //!< alias
                typedef Tile2D<T>           Tile; //!< alias
                typedef Memory::Troop<Tile> Code; //!< alias


                inline explicit Tiles2D(const size_t n, const vertex_t lo, const vertex_t up) :
                Leap(lo,up),
                code( new Code(n) ),
                ncpu(n)
                {
                    assert(ncpu>0);
                    setup();
                }

                inline explicit Tiles2D(const size_t n) :
                Leap(),
                code( new Code(n) ),
                ncpu(n)
                {
                    assert(ncpu>0);
                    setup();
                }

                inline virtual ~Tiles2D() noexcept
                {
                    assert(code); Destroy(code);
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t size()     const noexcept { return ncpu; }
                inline virtual size_t capacity() const noexcept { return ncpu; }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void remap(const vertex_t lo, const vertex_t up) noexcept
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
                    setup();
                }

            private:
                Y_Disable_Copy_And_Assign(Tiles2D);
                Code * const code; //!< inner code
                const size_t ncpu; //!< parallelism

                inline virtual const Tile & ask(const size_t indx) const noexcept
                {
                    assert(code);
                    assert(ncpu==code->size);
                    assert(indx>=1);
                    assert(indx<=ncpu);
                    return code->cxx[indx];
                }

                //! create all tiles
                inline void setup() noexcept
                {
                    assert(code);
                    code->free();
                    Tile * tile = code->addr;
                    while(code->size<ncpu) new (tile++) Tile(ncpu,Coerce(code->size)++,*this);
                    assert(ncpu==code->size);
                }
            };


        }
    }

}

#endif // !Y_Concurrent_Splitting_Tiles2D_Included

