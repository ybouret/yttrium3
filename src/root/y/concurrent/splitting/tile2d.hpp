
//! \file

#ifndef Y_Concurrent_Splitting_Tile2D_Included
#define Y_Concurrent_Splitting_Tile2D_Included 1

#include "y/concurrent/splitting/tile1d.hpp"
#include "y/mkl/v2d.hpp"
#include "y/swap.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"

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
                static const T _1 = 1; //!< alias

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

                //! cleanup
                inline virtual ~Leap2D() noexcept {}

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
                 \param indx in [0:items-1]
                 \return indx-t vertex
                 */
                inline vertex_t at(const size_t indx) const noexcept
                {
                    const T i  = (const T)indx; assert(i<items);
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
                Y_Disable_Assign(Leap2D); //!< dicarded

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

            //__________________________________________________________________
            //
            //
            //
            //! Horizontal Segment
            //
            //
            //__________________________________________________________________
            template <typename T>
            class HSegment
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T> vertex_t; //!< alias
                static const T   _1 = 1; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param s start \param w width > 0
                inline HSegment(const vertex_t &s, const T w) noexcept :
                start(s),width(w)
                {
                    assert(w>0);
                }

                //! duplicate \param s another segment
                inline HSegment(const HSegment &s) noexcept :
                start(s.start), width(s.width)
                {
                }

                //! duplicate with shift \param s source segment \param dy added to start.y
                inline HSegment(const HSegment &s, const T dy) noexcept :
                start( s.start.x, s.start.y + dy), width(s.width)
                {
                }

                //! cleanup
                inline ~HSegment() noexcept {}

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    return os << self.start << "+" << self.width << "->" << self.finish();
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return last vertex of segment
                inline vertex_t finish() const noexcept {
                    return vertex_t(start.x+width-1,start.y);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const vertex_t start; //!< starting point
                const T        width; //!< segment width

            private:
                Y_Disable_Assign(HSegment); //!< discarded
            };

            //__________________________________________________________________
            //
            //
            //
            //! 2D Tile
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tile2D : public Tile1D<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T>      vertex_t;        //!< alias
                typedef HSegment<T> Segment;         //!< alias
                static const T      _1          = 1; //!< alias
                static const size_t MaxSegments = 3; //!< alias
                static const size_t NeededBytes = MaxSegments * sizeof(Segment);           //!< for worksapce
                static const size_t NeededWords = Alignment::WordsGEQ<NeededBytes>::Count; //!< for workspace
                typedef   Segment (Tile2D::*Get)(const T) const; //!< get segment protocol

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! build from leap \param sz size \param rk rank \param leap source
                inline explicit Tile2D(const size_t     sz,
                                       const size_t     rk,
                                       const Leap2D<T> &leap) noexcept :
                Tile1D<T>(sz,rk,0,leap.items),
                span(0),
                get(0),
                cxx(0),
                wksp()
                {
                    build(leap);
                }

                //! cleanup
                inline virtual ~Tile2D() noexcept
                {
                }

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Tile2D &self)
                {
                    if(self.length<=0)
                        return os << Member::Empty;
                    else
                    {
                        assert(self.span>0);
                        return os << '|' << self[1].start << "->" << self[self.span].finish() << '|' << '=' << self.length << "/#" << self.span;
                    }
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \param indx indx in [1:nseg] \return indx-th segment
                inline Segment operator[](const T indx) const noexcept
                {
                    assert(indx>=1);
                    assert(indx<=span);
                    assert(get);
                    return (*this.*get)(indx);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T span; //!< number of segment(s)
            private:
                Y_Disable_Copy_And_Assign(Tile2D); //!< discarded
                Get const       get;               //!< get method
                Segment * const cxx;               //!< cxx[1..3]
                void *          wksp[NeededWords]; //!< inner space

                //______________________________________________________________
                //
                //
                // Design
                //
                //______________________________________________________________

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                inline Segment get1(const T) const noexcept
                {
                    assert(1==span);
                    assert(cxx);
                    return cxx[1];
                }

                inline Segment get2(const T i) const noexcept
                {
                    assert(2==span);
                    assert(cxx);
                    assert(i>=1);
                    assert(i<=2);
                    return cxx[i];
                }

                inline Segment getN(const T i) const noexcept
                {
                    assert(span>=3);
                    assert(cxx);
                    assert(i>=1);
                    assert(i<=span);
                    if(i<=1)
                    {
                        return cxx[1];
                    }
                    else
                    {
                        if(i>=span)
                        {
                            return cxx[3];
                        }
                        else
                        {
                            assert(i>=2);
                            assert(i<span);
                            return Segment(cxx[2],i);
                        }
                    }
                }



                inline void build(const Leap2D<T> &leap) noexcept
                {
                    if(this->length<=0) return;
                    
                    Coerce(cxx)        = static_cast<Segment*>( Y_BZero(wksp) )-1;
                    const vertex_t ini = leap.at(this->offset);
                    const vertex_t end = leap.at(this->utmost); assert(end.y>=ini.y);
                    Coerce(span)       = _1 + end.y - ini.y;    assert(span>=1);

                    switch( span )
                    {
                        case 1: // one segment from ini to end
                            new ( cxx+1 ) Segment(ini,_1+end.x-ini.x);
                            Coerce(get) = & Tile2D::get1;
                            break;

                        case 2: // two segments
                            new ( cxx+1 ) Segment(ini,_1+leap.upper.x-ini.x);
                            new ( cxx+2 ) Segment( vertex_t(leap.lower.x,end.y), _1+end.x - leap.lower.x);
                            Coerce(get) = & Tile2D::get2;
                            break;

                        default: assert(span>=3);
                            new ( cxx+1 ) Segment(ini,_1+leap.upper.x-ini.x);                              // first segment
                            new ( cxx+2 ) Segment( vertex_t(leap.lower.x,ini.y-_1),leap.width.x);          // bulk segment, offseted
                            new ( cxx+3 ) Segment( vertex_t(leap.lower.x,end.y), _1+end.x - leap.lower.x); // last segment
                            Coerce(get) = & Tile2D::getN;
                            break;
                    }

                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            };

        }

    }

}

#endif // !Y_Concurrent_Splitting_Tile2D_Included
