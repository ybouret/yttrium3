

//! \file

#ifndef Y_Concurrent_Splitting_Leap2D_Included
#define Y_Concurrent_Splitting_Leap2D_Included 1

#include "y/mkl/v2d.hpp"
#include "y/swap.hpp"


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
            //! 2D Leap
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Leap2D
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T> vertex_t; //!< alias
                static const T _1   = 1; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with valid (processed) data \param lo lower coordinate \param up upper coordinate
                inline explicit Leap2D(const vertex_t lo, const vertex_t up) noexcept :
                lower(lo),
                upper(up),
                width(0,0),
                items( computeItems() )
                {
                }

                //! setup with invalid (empty) coordinates
                inline explicit Leap2D() noexcept :
                lower(0,0),
                upper(0,0),
                width(0,0),
                items(0)
                {
                }

                //! duplicate \param leap another Leap2D
                inline Leap2D(const Leap2D &leap) noexcept :
                lower(leap.lower),
                upper(leap.upper),
                width(leap.width),
                items(leap.items)
                {
                }


                //! cleanup
                inline virtual ~Leap2D() noexcept
                {
                    const vertex_t _v0(0,0);
                    Coerce(lower) = _v0;
                    Coerce(upper) = _v0;
                    Coerce(width) = _v0;
                    Coerce(items) = 0;
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                inline friend bool operator==(const Leap2D &lhs,
                                              const Leap2D &rhs) noexcept
                {
                    return lhs.lower == rhs.lower && lhs.upper == rhs.upper;
                }

                inline friend bool operator!=(const Leap2D &lhs,
                                              const Leap2D &rhs) noexcept
                {
                    return lhs.lower != rhs.lower || lhs.upper != rhs.upper;
                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

                //! find vertex by index
                /**
                 \param i in [0:items-1]
                 \return i-th vertex
                 */
                inline vertex_t at(const T i) const noexcept
                {
                    assert(i<items);
                    const T y0 = (const T)(i / width.x);
                    const T x0 = (const T)(i % width.x);
                    return vertex_t(x0+lower.x,y0+lower.y);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const vertex_t lower; //!< lower coordinate
                const vertex_t upper; //!< upper coordinate
                const vertex_t width; //!< width in each dimension
                const T        items; //!< number of items



            private:
                Y_Disable_Assign(Leap2D); //!< discarded

                //! \return items from processed inpt
                inline T computeItems() noexcept
                {
                    if(lower.x>upper.x) CoerceSwap(lower.x,upper.x);
                    if(lower.y>upper.y) CoerceSwap(lower.x,upper.x);
                    Coerce(width.x) = _1 + upper.x - lower.x;
                    Coerce(width.y) = _1 + upper.y - lower.y;
                    return width.x * width.y;
                }

            };
        }

    }

}

#endif // !Y_Concurrent_Splitting_Leap2D_Included
