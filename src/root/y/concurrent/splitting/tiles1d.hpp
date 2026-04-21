
//! \file

#ifndef Y_Concurrent_Splitting_Tiles1D_Included
#define Y_Concurrent_Splitting_Tiles1D_Included 1

#include "y/concurrent/splitting/tile1d.hpp"
#include "y/container/contiguous/readable.hpp"
#include "y/memory/troop.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {
            template <typename T>
            class Leap1D
            {
            public:
                inline   Leap1D(const T dataOffset,
                                       const T dataLength) noexcept :
                offset(dataOffset),
                length(dataLength)
                {
                }

                inline Leap1D(const Leap1D &other) noexcept :
                offset(other.offset),
                length(other.length)
                {
                }


                inline virtual ~Leap1D()  noexcept
                {
                    Coerce(offset) = 0;
                    Coerce(length) = 0;
                }

                inline friend bool operator==(const Leap1D &lhs, const Leap1D &rhs) noexcept
                {
                    return lhs.offset == rhs.offset && lhs.length == rhs.length;
                }

                inline friend bool operator!=(const Leap1D &lhs, const Leap1D &rhs) noexcept
                {
                    return lhs.offset != rhs.offset || lhs.length!= rhs.length;
                }


                const T offset;
                const T length;

            private:
                Y_Disable_Assign(Leap1D);

            };

            template <typename T>
            class Tiles1D :
            public Leap1D<T>,
            public ContiguousReadable< Tile1D<T> >
            {
            public:
                typedef Leap1D<T>           Leap;
                typedef Tile1D<T>           Tile;
                typedef Memory::Troop<Tile> Code;

                using Leap::offset;
                using Leap::length;

                inline explicit Tiles1D(const size_t n, const T offset, const T length) :
                Leap(offset,length),
                code( new Code(n) ),
                ncpu(n)
                {
                    setup();
                }

                inline virtual ~Tiles1D() noexcept { assert(code); Destroy(code); }

                inline virtual size_t size()     const noexcept { return ncpu; }
                inline virtual size_t capacity() const noexcept { return ncpu; }

            private:
                Y_Disable_Copy_And_Assign(Tiles1D);
                Code * const code;
                const size_t ncpu;

                inline virtual const Tile & ask(const size_t indx) const noexcept
                {
                    assert(code);
                    assert(ncpu==code->size);
                    assert(indx>=1);
                    assert(indx<=ncpu);
                    return code->cxx[indx];
                }

                inline void setup() noexcept
                {
                    assert(code);
                    code->free();
                    Yttrium_BZero(code->addr,code->bytes);
                    Tile * tile = code->addr;
                    while(code->size<ncpu)
                        new (tile++) Tile(ncpu,Coerce(code->size)++,offset,length);
                    assert(ncpu==code->size);
                }
            };

        }

    }

}

#endif // !Y_Concurrent_Splitting_Tiles1D_Included

