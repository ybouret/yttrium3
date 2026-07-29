

//! \file

#ifndef Y_Ink_Ops_MinMax_Included
#define Y_Ink_Ops_MinMax_Included 1

#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {
        namespace Ops
        {

            template <typename T>
            class PixelRange
            {
            public:
                inline  PixelRange(const T &v) : vmin(v), vmax(v) { }
                inline ~PixelRange() noexcept { }

                inline PixelRange(const PixelRange &p) :
                vmin(p.vmin),
                vmax(p.vmax)
                {
                }

                template <typename U> inline
                PixelRange(const CopyOf_ &, const PixelRange<U> &p) :
                vmin(p.vmin),
                vmax(p.vmax)
                {
                }


                inline void operator()(const T &v)
                {
                    assert(vmin<=vmax);
                    if(v>vmax)
                        vmax = v;
                    else
                        if(v<vmin)
                            vmin = v;
                }

                inline void operator()(const PixelRange &p)
                {
                    InSituMin(vmin,p.vmin);
                    InSituMax(vmax,p.vmax);
                }



                T vmin;
                T vmax;

            private:
                Y_Disable_Assign(PixelRange);

            };

            template <typename PIXMAP> static inline
            void MinMaxCB(Tile &tile, PIXMAP &pixmap)
            {
                if(tile.isEmpty()) return;
                typedef typename PIXMAP::MutableType Type;
                typedef PixelRange<Type>             RangeType;

                RangeType &res = tile.as<RangeType>();
                new (&res) RangeType( pixmap(tile.start()) );
                for(unit_t k=tile.span;k>0;--k)
                {
                    const Segment                s = tile[k];
                    const unit_t                 y = s.start.y;
                    const typename PIXMAP::Row & r = pixmap(y);
                    for(unit_t x=s.start.x,i=s.width;i>0;--i,++x)
                        res( r(x) );
                }
            }

            template <typename PIXMAP> inline
            PixelRange<typename PIXMAP::Type> MinMax(Broker  & broker,
                                                     PIXMAP  & pixmap)
            {
                typedef typename PIXMAP::MutableType Type;
                typedef PixelRange<Type>             RangeType;

                // prepare
                broker.map(pixmap);
                broker.ensureCache( sizeof(RangeType) );

                // collect each tile
                broker.apply(pixmap,MinMaxCB<PIXMAP>);


                // reduction
                size_t     i = broker.size();
                RangeType  v = broker.sub(i).as<RangeType>();
                for(--i;i>0;--i) v( broker.sub(i).as<RangeType>() );
                return PixelRange<typename PIXMAP::Type>(CopyOf,v);
            }

        }

    }

}

#endif // !Y_Ink_Ops_MinMax_Included


