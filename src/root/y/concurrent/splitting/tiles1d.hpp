
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
            //__________________________________________________________________
            //
            //
            //
            //! 1D Leap
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Leap1D
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param dataOffset data offset
                 \param dataLength data length
                 */
                inline   Leap1D(const T dataOffset,
                                const T dataLength) noexcept :
                offset(dataOffset),
                length(dataLength) {
                }

                //! duplicate \param other another leap
                inline Leap1D(const Leap1D &other) noexcept :
                offset(other.offset),
                length(other.length) {
                }

                //! cleanup
                inline virtual ~Leap1D()  noexcept {
                    Coerce(offset) = 0;
                    Coerce(length) = 0;
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                inline friend bool operator==(const Leap1D &lhs, const Leap1D &rhs) noexcept
                {
                    return lhs.offset == rhs.offset && lhs.length == rhs.length;
                }

                inline friend bool operator!=(const Leap1D &lhs, const Leap1D &rhs) noexcept
                {
                    return lhs.offset != rhs.offset || lhs.length!= rhs.length;
                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T offset; //!< current offset
                const T length; //!< current length

            private:
                Y_Disable_Assign(Leap1D); //!< discarded

            };

            //__________________________________________________________________
            //
            //
            //
            //! 1D (reusable) Tiles
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles1D :
            public Leap1D<T>,
            public ContiguousReadable< Tile1D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Leap1D<T>           Leap; //!< alias
                typedef Tile1D<T>           Tile; //!< alias
                typedef Memory::Troop<Tile> Code; //!< alias
                using Leap::offset;
                using Leap::length;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param n          ncpu > 0
                 \param dataOffset data offset
                 \param dataLength data length
                 */
                inline explicit Tiles1D(const size_t n, const T dataOffset, const T dataLength) :
                Leap(dataOffset,dataLength),
                code( new Code(n) ),
                ncpu(n)
                {
                    assert(ncpu>0);
                    setup();
                }

                //! cleanup
                inline virtual ~Tiles1D() noexcept { assert(code); Destroy(code); }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! remap a new region, keeping same level of parallelism
                /**
                 \param dataOffset data offset
                 \param dataLength data length
                 */
                inline void remap(const T dataOffset, const T dataLength)
                {
                    {
                        Leap &     oldLeap = *this;
                        const Leap newLeap(dataOffset,dataLength);
                        if(oldLeap == newLeap) return; // unchanged
                        Coerce(oldLeap.offset) = newLeap.offset;
                        Coerce(oldLeap.length) = newLeap.length;
                    }
                    setup();
                }

                //______________________________________________________________
                //
                //
                // Interfae
                //
                //______________________________________________________________
                inline virtual size_t size()     const noexcept { return ncpu; }
                inline virtual size_t capacity() const noexcept { return ncpu; }

            private:
                Y_Disable_Copy_And_Assign(Tiles1D); //!< discarded
                Code * const code;                  //!< inner code
                const size_t ncpu;                  //!< number of CPU

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
                    while(code->size<ncpu)
                        new (tile++) Tile(ncpu,Coerce(code->size)++,offset,length);
                    assert(ncpu==code->size);
                }
            };

        }

    }

}

#endif // !Y_Concurrent_Splitting_Tiles1D_Included

