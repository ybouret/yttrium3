
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
            template <typename T>
            class Leap2D
            {
            public:
                typedef V2D<T> vertex_t;
                static const T _1 = 1;

                inline explicit Leap2D(const vertex_t lo, const vertex_t up) noexcept :
                lower(lo),
                upper(up),
                width(0,0),
                items( computeItems() )
                {
                }

                inline explicit Leap2D() noexcept :
                lower(0,0),
                upper(0,0),
                width(0,0),
                items(0)
                {
                }

                inline virtual ~Leap2D() noexcept {}

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


                vertex_t at(const size_t indx) const noexcept
                {
                    const T i  = (const T)indx; assert(i<items);
                    const T y0 = (const T)(i / width.x);
                    const T x0 = (const T)(i % width.x);
                    return vertex_t(x0+lower.x,y0+upper.x);
                }

                const vertex_t lower;
                const vertex_t upper;
                const vertex_t width;
                const T        items;



            private:
                Y_Disable_Assign(Leap2D);

                inline T computeItems() noexcept
                {
                    if(lower.x>upper.x) CoerceSwap(lower.x,upper.x);
                    if(lower.y>upper.y) CoerceSwap(lower.x,upper.x);
                    Coerce(width.x) = _1 + upper.x - lower.x;
                    Coerce(width.y) = _1 + upper.y - lower.y;
                    return width.x * width.y;
                }

            };

            template <typename T>
            class HSegment
            {
            public:
                typedef V2D<T> vertex_t;
                static const T      _1 = 1;
                inline HSegment(const vertex_t &s, const T w) noexcept :
                start(s),width(w)
                {
                    assert(w>0);
                }

                inline HSegment(const HSegment &s) noexcept :
                start(s.start), width(s.width)
                {
                }

                inline HSegment(const HSegment &s, const T dy) noexcept :
                start( s.start.x, s.start.y + dy), width(s.width)
                {
                }


                inline ~HSegment() noexcept {}

                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    return os << self.start << "+" << self.width << "->" << self.finish();
                }

                inline vertex_t finish() const noexcept {
                    return vertex_t(start.x+width-1,start.y);
                }

                const vertex_t start;
                const T        width;

            private:
                Y_Disable_Assign(HSegment);
            };


            template <typename T>
            class Tile2D : public Tile1D<T>
            {
            public:
                typedef V2D<T>      vertex_t;
                typedef HSegment<T> Segment;
                typedef   Segment (Tile2D::*Get)(const T) const;
                static const T      _1          = 1;
                static const size_t MaxSegments = 3;
                static const size_t NeededBytes = MaxSegments * sizeof(Segment);
                static const size_t NeededWords = Alignment::WordsGEQ<NeededBytes>::Count;

                inline explicit Tile2D(const size_t     sz,
                                       const size_t     rk,
                                       const Leap2D<T> &leap) noexcept :
                Tile1D<T>(sz,rk,0,leap.items),
                size(0),
                get(0),
                cxx(0),
                wksp()
                {
                    build(leap);
                }

                inline virtual ~Tile2D() noexcept
                {
                }

                inline friend std::ostream & operator<<(std::ostream &os, const Tile2D &self)
                {
                    if(self.length<=0)
                        return os << Member::Empty;
                    else
                    {
                        assert(self.size>0);
                        return os << '|' << self[1].start << "->" << self[self.size].finish() << '|' << '=' << self.length;
                    }
                }

                inline Segment operator[](const T indx) const noexcept
                {
                    assert(indx>=1);
                    assert(indx<=size);
                    assert(get);
                    return (*this.*get)(indx);
                }

                const T size;
            private:
                Y_Disable_Copy_And_Assign(Tile2D);
                Get const       get;
                Segment * const cxx;
                void *          wksp[ NeededWords ];

                inline Segment get1(const T) const noexcept
                {
                    assert(1==size);
                    assert(cxx);
                    return cxx[1];
                }

                inline Segment get2(const T i) const noexcept
                {
                    assert(2==size);
                    assert(cxx);
                    assert(i>=1);
                    assert(i<=2);
                    return cxx[i];
                }

                inline Segment getN(const T i) const noexcept
                {
                    assert(size>=3);
                    assert(cxx);
                    assert(i>=1);
                    assert(i<=size);
                    if(i<=1)
                    {
                        return cxx[1];
                    }
                    else
                    {
                        if(i>=size)
                        {
                            return cxx[3];
                        }
                        else
                        {
                            assert(i>=2);
                            assert(i<size);
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
                    Coerce(size)       = _1 + end.y - ini.y;    assert(size>=1);
                   // std::cerr << "\t" << ini << " -> " << end << " #" << size << std::endl;

                    switch( size )
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

                        default: assert(size>=3);
                            new ( cxx+1 ) Segment(ini,_1+leap.upper.x-ini.x);                              // first segment
                            new ( cxx+2 ) Segment( vertex_t(leap.lower.x,ini.y-_1),leap.width.x);          // bulk segment, offseted
                            new ( cxx+3 ) Segment( vertex_t(leap.lower.x,end.y), _1+end.x - leap.lower.x); // last segment
                            Coerce(get) = & Tile2D::getN;
                            break;
                    }

                }
            };

        }

    }

}

#endif // !Y_Concurrent_Splitting_Tile2D_Included
