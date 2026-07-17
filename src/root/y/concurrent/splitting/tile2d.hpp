
//! \file

#ifndef Y_Concurrent_Splitting_Tile2D_Included
#define Y_Concurrent_Splitting_Tile2D_Included 1

#include "y/concurrent/splitting/leap2d.hpp"
#include "y/concurrent/splitting/tile1d.hpp"
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

#define Y_Concurrent_Tile2D() \
span(0), \
get(0), \
cxx(0), \
wksp()
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
                                       Lockable        &lk,
                                       const Leap2D<T> &leap) noexcept :
                Tile1D<T>(sz,rk,lk,0,leap.items),
                Y_Concurrent_Tile2D()
                {
                    build(leap);
                }

                inline explicit Tile2D(const Context   & ctx,
                                       const Leap2D<T> & leap) noexcept :

                Tile1D<T>(ctx,0,leap.items),
                Y_Concurrent_Tile2D()
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

                //! \param i i in [1:nseg] \return indx-th segment
                inline Segment operator[](const T i) const noexcept
                {
                    assert(i>=1);
                    assert(i<=span);
                    assert(get);
                    return (*this.*get)(i);
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
